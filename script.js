document.addEventListener("DOMContentLoaded", function () {
  const sections = document.querySelectorAll("main section");
  let lastScrollTop = window.scrollY;

  const observer = new IntersectionObserver((entries) => {
    entries.forEach(entry => {
      if (entry.isIntersecting) {
        entry.target.classList.add("visible");
      } else {
        if (window.scrollY < lastScrollTop) {
          entry.target.classList.remove("visible");
          entry.target.classList.add("collapsed");
        }
      }
    });
  }, { threshold: 0.2 });

  sections.forEach(section => {
    observer.observe(section);
  });

  window.addEventListener("scroll", () => {
    const st = window.scrollY;

    if (st > lastScrollTop) {
    } else {
    }

    lastScrollTop = st <= 0 ? 0 : st;
  });
});