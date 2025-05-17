document.addEventListener("DOMContentLoaded", function () {
    const sections = document.querySelectorAll("main section");
  
    const observer = new IntersectionObserver(entries => {
      entries.forEach(entry => {
        if (entry.isIntersecting) {
          entry.target.classList.add("visible");
        }
      });
    }, { threshold: 0.3 });
  
    sections.forEach(section => {
      observer.observe(section);
    });
  });