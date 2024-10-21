// casino.js
document.addEventListener('DOMContentLoaded', function() {
    const reel1 = document.getElementById('reel1');
    const reel2 = document.getElementById('reel2');
    const reel3 = document.getElementById('reel3');
    const spinButton = document.getElementById('spinButton');
    const result = document.getElementById('result');
    const symbols = ['🍒', '🍋', '🍌', '💎', '🐒', '7️⃣'];

    spinButton.addEventListener('click', function() {
        // Добавляем класс анимации
        reel1.classList.add('spin');
        reel2.classList.add('spin');
        reel3.classList.add('spin');

        result.textContent = 'Крутим барабаны...';

        // Отключаем кнопку во время вращения
        spinButton.disabled = true;

        setTimeout(() => {
            // Убираем класс анимации
            reel1.classList.remove('spin');
            reel2.classList.remove('spin');
            reel3.classList.remove('spin');

            // Генерируем случайные символы
            const symbol1 = symbols[Math.floor(Math.random() * symbols.length)];
            const symbol2 = symbols[Math.floor(Math.random() * symbols.length)];
            const symbol3 = symbols[Math.floor(Math.random() * symbols.length)];

            // Отображаем символы на барабанах
            reel1.textContent = symbol1;
            reel2.textContent = symbol2;
            reel3.textContent = symbol3;

            // Проверяем результат
            if (symbol1 === symbol2 && symbol2 === symbol3) {
                result.textContent = '🎉 Поздравляем! Вы выиграли! 🎉';
            } else if (symbol1 === symbol2 || symbol2 === symbol3 || symbol1 === symbol3) {
                result.textContent = 'Почти повезло! Попробуйте еще раз.';
            } else {
                result.textContent = 'Увы, вы проиграли. Попробуйте снова!';
            }

            // Включаем кнопку обратно
            spinButton.disabled = false;

        }, 1000);
    });
});
