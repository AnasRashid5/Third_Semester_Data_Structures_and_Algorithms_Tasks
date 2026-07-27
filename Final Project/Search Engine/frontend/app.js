(() => {
    // ISSUE FIX: Uses same-origin /api/* URLs so the C++ server can serve both UI and JSON (not file://).
    const form            = document.getElementById('searchForm');
    const input           = document.getElementById('searchInput');
    const clearBtn        = document.getElementById('clearBtn');
    const searchBtn       = document.getElementById('searchBtn');
    const autocomplete    = document.getElementById('autocomplete');
    const autocompleteList = document.getElementById('autocompleteList');
    const results         = document.getElementById('results');
    const resultsMeta     = document.getElementById('resultsMeta');
    const resultsList     = document.getElementById('resultsList');
    const main            = document.getElementById('main');

    // ISSUE FIX: Changed luckyBtn references to historyBtn and related panel
    // elements. The old luckyBtn no longer exists in the HTML.
    const historyBtn      = document.getElementById('historyBtn');
    const historyPanel    = document.getElementById('historyPanel');
    const historyCloseBtn = document.getElementById('historyCloseBtn');
    const historyList     = document.getElementById('historyList');
    const historyEmpty    = document.getElementById('historyEmpty');

    // ISSUE FIX: Document modal elements
    const docModal        = document.getElementById('docModal');
    const docModalTitle   = document.getElementById('docModalTitle');
    const docModalText    = document.getElementById('docModalText');
    const docModalClose   = document.getElementById('docModalClose');

    let activeIndex = -1;
    let inputTimer;

    // ISSUE FIX: In-memory array holds every unique query the user has searched
    // during this session. Used by the History panel and written to localStorage
    // so it survives page refreshes.
    let searchHistory = JSON.parse(localStorage.getItem('googolHistory') || '[]');

    // ─── Autocomplete ────────────────────────────────────────────────────────

    // ISSUE FIX: Replaces placeholder suggestions with the C++ Trie API.
    async function getSuggestions(query) {
        const response = await fetch('/api/autocomplete?prefix=' + encodeURIComponent(query));
        if (!response.ok) throw new Error('Autocomplete request failed.');
        const data = await response.json();
        return data.suggestions || [];
    }

    async function renderAutocomplete(query) {
        autocompleteList.innerHTML = '';
        activeIndex = -1;

        if (!query.trim()) {
            autocomplete.classList.remove('open');
            input.setAttribute('aria-expanded', 'false');
            return;
        }

        try {
            const suggestions = await getSuggestions(query);

            if (input.value.trim() !== query.trim()) return;

            if (suggestions.length === 0) {
                autocomplete.classList.remove('open');
                input.setAttribute('aria-expanded', 'false');
                return;
            }

            suggestions.forEach((suggestion, index) => {
                const item = document.createElement('li');
                item.textContent = suggestion;
                item.setAttribute('role', 'option');
                item.id = 'ac-item-' + index;
                item.addEventListener('click', () => {
                    input.value = suggestion;
                    autocomplete.classList.remove('open');
                    runSearch(suggestion);
                });
                autocompleteList.appendChild(item);
            });

            autocomplete.classList.add('open');
            input.setAttribute('aria-expanded', 'true');
        } catch (error) {
            autocomplete.classList.remove('open');
        }
    }

    // ISSUE FIX: Waits briefly before each API call so typing does not flood the server.
    input.addEventListener('input', () => {
        clearBtn.classList.toggle('visible', input.value.length > 0);
        clearTimeout(inputTimer);
        inputTimer = setTimeout(() => renderAutocomplete(input.value), 180);
    });

    input.addEventListener('focus', () => {
        if (input.value.trim()) renderAutocomplete(input.value);
    });

    document.addEventListener('click', event => {
        if (!event.target.closest('.search-wrap')) autocomplete.classList.remove('open');
    });

    input.addEventListener('keydown', event => {
        const items = Array.from(autocompleteList.querySelectorAll('li[role="option"]'));
        if (!autocomplete.classList.contains('open') || items.length === 0) return;

        if (event.key === 'ArrowDown') {
            event.preventDefault();
            activeIndex = (activeIndex + 1) % items.length;
        } else if (event.key === 'ArrowUp') {
            event.preventDefault();
            activeIndex = (activeIndex - 1 + items.length) % items.length;
        } else if (event.key === 'Enter' && activeIndex >= 0) {
            event.preventDefault();
            input.value = items[activeIndex].textContent;
            autocomplete.classList.remove('open');
            runSearch(input.value);
        } else if (event.key === 'Escape') {
            autocomplete.classList.remove('open');
        } else {
            return;
        }

        items.forEach((item, index) => item.classList.toggle('active', index === activeIndex));
    });

    clearBtn.addEventListener('click', () => {
        input.value = '';
        clearBtn.classList.remove('visible');
        autocomplete.classList.remove('open');
        input.focus();
    });

    // ─── Result rendering helpers ─────────────────────────────────────────────

    function escapeHtml(value) {
        const element = document.createElement('div');
        element.textContent = value;
        return element.innerHTML;
    }

    // ISSUE FIX: Raw file paths like "storage/documents/doc5_web_technologies.txt"
    // were shown verbatim in the result cards which looked broken. This function
    // converts the filename into a readable title (e.g. "Web Technologies").
    function docTitle(docPath) {
        const base = docPath.split(/[\\/]/).pop().replace(/\.txt$/i, '');
        // Strip leading "docN_" prefix if present (e.g. "doc5_web_technologies" → "web technologies")
        const stripped = base.replace(/^doc\d+_/i, '');
        // Replace underscores with spaces and title-case each word
        return stripped.replace(/_/g, ' ').replace(/\b\w/g, c => c.toUpperCase());
    }

    // ─── History panel ────────────────────────────────────────────────────────

    // ISSUE FIX: History panel was missing entirely. This function rebuilds the
    // <ul> in the aside#historyPanel from the in-memory searchHistory array.
    function renderHistoryPanel() {
        historyList.innerHTML = '';
        if (searchHistory.length === 0) {
            historyEmpty.style.display = 'block';
            return;
        }
        historyEmpty.style.display = 'none';
        // Show newest first
        [...searchHistory].reverse().forEach(query => {
            const li = document.createElement('li');
            li.className = 'history-item';
            li.innerHTML = `
                <svg width="13" height="13" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" aria-hidden="true"><polyline points="1 4 1 10 7 10"></polyline><path d="M3.51 15a9 9 0 1 0 .49-3.76"></path></svg>
                <span>${escapeHtml(query)}</span>
            `;
            li.addEventListener('click', () => {
                input.value = query;
                clearBtn.classList.add('visible');
                closeHistoryPanel();
                runSearch(query);
            });
            historyList.appendChild(li);
        });
    }

    function openHistoryPanel() {
        renderHistoryPanel();
        historyPanel.classList.add('open');
        historyPanel.setAttribute('aria-hidden', 'false');
        historyBtn.setAttribute('aria-expanded', 'true');
    }

    function closeHistoryPanel() {
        historyPanel.classList.remove('open');
        historyPanel.setAttribute('aria-hidden', 'true');
        historyBtn.setAttribute('aria-expanded', 'false');
    }

    // ISSUE FIX: Wires the new historyBtn to toggle the history panel.
    historyBtn.addEventListener('click', () => {
        if (historyPanel.classList.contains('open')) {
            closeHistoryPanel();
        } else {
            openHistoryPanel();
        }
    });

    historyCloseBtn.addEventListener('click', closeHistoryPanel);

    // Close panel when user clicks outside of it
    document.addEventListener('click', event => {
        if (
            historyPanel.classList.contains('open') &&
            !event.target.closest('#historyPanel') &&
            !event.target.closest('#historyBtn')
        ) {
            closeHistoryPanel();
        }
    });

    // ─── Document Modal ───────────────────────────────────────────────────────

    // ISSUE FIX: Function to open the document modal and fetch its content
    async function openDocModal(docPath, docName) {
        docModalTitle.textContent = docName;
        docModalText.textContent = 'Loading document...';
        docModal.classList.add('open');
        docModal.setAttribute('aria-hidden', 'false');

        try {
            const response = await fetch('/api/document?name=' + encodeURIComponent(docPath));
            if (!response.ok) throw new Error('Failed to load document');
            const text = await response.text();
            docModalText.textContent = text;
        } catch (error) {
            docModalText.textContent = 'Error loading document content.';
        }
    }

    docModalClose.addEventListener('click', () => {
        docModal.classList.remove('open');
        docModal.setAttribute('aria-hidden', 'true');
    });

    // Close modal when user clicks outside of it
    document.addEventListener('click', event => {
        if (docModal.classList.contains('open') && event.target === docModal) {
            docModal.classList.remove('open');
            docModal.setAttribute('aria-hidden', 'true');
        }
    });

    // Event delegation for result item titles to open the modal
    resultsList.addEventListener('click', event => {
        const titleEl = event.target.closest('.title');
        if (titleEl) {
            const docPath = titleEl.getAttribute('data-doc');
            const docName = titleEl.getAttribute('data-name');
            if (docPath) {
                openDocModal(docPath, docName);
            }
        }
    });

    // ─── History tracking helper ──────────────────────────────────────────────

    // ISSUE FIX: Adds a query to the in-memory history array and persists it to
    // localStorage so it survives page reloads. Duplicate consecutive searches
    // are not added again.
    function addToHistory(query) {
        if (searchHistory[searchHistory.length - 1] === query) return;
        searchHistory.push(query);
        // Keep only the 50 most recent entries to avoid unbounded growth
        if (searchHistory.length > 50) searchHistory.shift();
        localStorage.setItem('googolHistory', JSON.stringify(searchHistory));
    }

    // ─── Browser history (Back / Forward button) ──────────────────────────────

    // ISSUE FIX: runSearch now calls history.pushState so the browser's Back
    // button records each query as a separate navigation entry. Without this,
    // pressing Back would leave the search results page immediately with no way
    // to return to the previous query.
    function pushHistoryState(query) {
        const url = query ? ('?q=' + encodeURIComponent(query)) : location.pathname;
        history.pushState({ query }, '', url);
    }

    // ISSUE FIX: Listening for the popstate event lets us restore the previous
    // search when the user clicks the browser's Back or Forward button.
    window.addEventListener('popstate', event => {
        const query = event.state && event.state.query ? event.state.query : '';
        if (query) {
            input.value = query;
            clearBtn.classList.toggle('visible', query.length > 0);
            runSearch(query, false); // false = do not push another state entry
        } else {
            // Back to the empty home page state
            input.value = '';
            clearBtn.classList.remove('visible');
            results.classList.remove('visible');
            main.classList.remove('has-results');
            resultsMeta.textContent = '';
            resultsList.innerHTML = '';
        }
    });

    // On first load, restore a query from the URL if present (e.g. after a page refresh)
    (function restoreFromUrl() {
        const params = new URLSearchParams(location.search);
        const q = params.get('q');
        if (q) {
            input.value = q;
            clearBtn.classList.add('visible');
            // Replace the initial state so that the popstate above can clear it
            history.replaceState({ query: q }, '', location.href);
            runSearch(q, false);
        } else {
            history.replaceState({ query: '' }, '', location.href);
        }
    })();

    // ─── Core search ──────────────────────────────────────────────────────────

    // ISSUE FIX: Replaces demo output with ranked results returned by the C++ Indexer.
    // Second parameter `pushState` controls whether a new browser history entry is
    // created (true by default; false when restoring from popstate or URL).
    async function runSearch(query, pushState = true) {
        query = (query || input.value).trim();
        autocomplete.classList.remove('open');

        if (!query) {
            results.classList.remove('visible');
            main.classList.remove('has-results');
            return;
        }

        main.classList.add('has-results');
        results.classList.add('visible');
        resultsMeta.textContent = 'Searching…';
        resultsList.innerHTML = '';

        // ISSUE FIX: Push a browser history entry for this query so the Back
        // button navigates to the previous search instead of leaving the page.
        if (pushState) {
            pushHistoryState(query);
        }

        // Record query in the in-memory + localStorage history
        addToHistory(query);

        try {
            const response = await fetch('/api/search?q=' + encodeURIComponent(query));
            if (!response.ok) throw new Error('Search request failed.');
            const data = await response.json();

            resultsMeta.textContent = data.results.length
                ? data.results.length + ' result(s) for "' + query + '"'
                : (data.message || 'No results found.');

            if (data.results.length === 0) {
                resultsList.innerHTML = '<div class="empty-results"><div class="glyph">🔍</div><p>' +
                    escapeHtml(data.message || 'No matching documents found.') + '</p></div>';
                return;
            }

            // ISSUE FIX: Result cards previously showed raw file paths and a plain
            // "Matched score: N" snippet. Now they show a human-readable document
            // title derived from the filename and a formatted relevance badge.
            // Added data attributes to the title to enable click-to-view in modal.
            resultsList.innerHTML = data.results.map((result, index) => {
                const title = docTitle(result.document);
                return `
                    <article class="result-item">
                        <div class="url">${escapeHtml(result.document)}</div>
                        <h2 class="title" data-doc="${escapeHtml(result.document)}" data-name="${escapeHtml(title)}" title="Click to view full document">${escapeHtml(title)}</h2>
                        <p class="snippet">
                            Relevance score: <strong>${result.score}</strong>
                            &nbsp;·&nbsp; Result ${index + 1} of ${data.results.length}
                        </p>
                    </article>
                `;
            }).join('');
        } catch (error) {
            resultsMeta.textContent = 'Could not connect to the search server.';
            resultsList.innerHTML = '<div class="empty-results"><div class="glyph">⚠️</div><p>Start the C++ server, then refresh this page.</p></div>';
        }
    }

    // ─── Form event wiring ────────────────────────────────────────────────────

    form.addEventListener('submit', event => {
        event.preventDefault();
        runSearch(input.value);
    });

    searchBtn.addEventListener('click', () => runSearch(input.value));
})();
