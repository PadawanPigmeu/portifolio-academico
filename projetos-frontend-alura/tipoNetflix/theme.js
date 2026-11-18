/**
 * Script para gerenciar Dark Mode e Light Mode
 * Salva preferência do usuário em localStorage
 */

// Identifica o elemento do botão de toggle
const themeToggle = document.getElementById('themeToggle');
// Obtém a raiz do documento HTML
const htmlElement = document.documentElement;

/**
 * Inicializa o tema baseado na preferência salva ou preferência do sistema
 */
function initTheme() {
    // Verifica se há preferência salva no localStorage
    const savedTheme = localStorage.getItem('theme');
    
    // Se há preferência salva, usa ela
    if (savedTheme) {
        htmlElement.setAttribute('data-theme', savedTheme);
        updateThemeButton(savedTheme);
    } else {
        // Caso contrário, detecta preferência do sistema (dark ou light)
        const prefersDark = window.matchMedia('(prefers-color-scheme: dark)').matches;
        const initialTheme = prefersDark ? 'dark' : 'light';
        htmlElement.setAttribute('data-theme', initialTheme);
        updateThemeButton(initialTheme);
    }
}

/**
 * Atualiza apenas o emoji do botão conforme o tema
 * @param {string} theme - tema atual ('dark' ou 'light')
 */
function updateThemeButton(theme) {
    if (theme === 'dark') {
        themeToggle.textContent = '☀️'; /* sol para trocar para light mode */
        themeToggle.classList.remove('light-mode');
        themeToggle.classList.add('dark-mode');
    } else {
        themeToggle.textContent = '🌙'; /* lua para trocar para dark mode */
        themeToggle.classList.remove('dark-mode');
        themeToggle.classList.add('light-mode');
    }
}

/**
 * Alterna entre temas e salva no localStorage
 */
function toggleTheme() {
    // Obtém tema atual
    const currentTheme = htmlElement.getAttribute('data-theme') || 'dark';
    // Define novo tema (inverso do atual)
    const newTheme = currentTheme === 'dark' ? 'light' : 'dark';
    
    // Aplica novo tema ao elemento raiz
    htmlElement.setAttribute('data-theme', newTheme);
    // Salva preferência no localStorage
    localStorage.setItem('theme', newTheme);
    // Atualiza texto do botão
    updateThemeButton(newTheme);
}

// Event listener: detecta clique no botão de toggle
themeToggle.addEventListener('click', toggleTheme);

// Inicializa tema ao carregar a página
document.addEventListener('DOMContentLoaded', initTheme);

// Detecta mudança de preferência do sistema (quando usuário muda nas configurações do SO)
window.matchMedia('(prefers-color-scheme: dark)').addEventListener('change', (event) => {
    if (!localStorage.getItem('theme')) {
        // Se não há preferência salva, respeita mudança do sistema
        const newTheme = event.matches ? 'dark' : 'light';
        htmlElement.setAttribute('data-theme', newTheme);
        updateThemeButton(newTheme);
    }
});
