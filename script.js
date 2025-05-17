document.addEventListener("DOMContentLoaded", function () {
  const sections = document.querySelectorAll("main section");

  function handleScroll() {
    const st = window.scrollY;

    sections.forEach(section => {
      const rect = section.getBoundingClientRect();

      if (!section.classList.contains("visible") && rect.top < window.innerHeight * 0.8) {
        section.classList.remove("collapsed");
        section.classList.add("visible");

        const image = section.querySelector(".image");
        if (image) {
          image.classList.add("visible");
        }
      }

      if (rect.bottom < -50 && section.classList.contains("visible")) {
        section.classList.remove("visible");
        section.classList.add("collapsed");

        const image = section.querySelector(".image");
        if (image) {
          image.classList.remove("visible");
          image.classList.add("collapsed");
        }
      }

      if (section.classList.contains("collapsed") && rect.top < window.innerHeight * 0.8) {
        section.classList.remove("collapsed");
        section.classList.add("visible");

        const image = section.querySelector(".image");
        if (image) {
          image.classList.remove("collapsed");
          image.classList.add("visible");
        }
      }
    });
  }

  window.addEventListener("scroll", handleScroll);
  window.addEventListener("load", handleScroll);
});