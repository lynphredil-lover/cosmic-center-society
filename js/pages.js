// Jump to a specific section on the page
function JumpTo(link, id) {
  window.location.href = link + "#" + id;
}

// Adjust content margin based on header height (on load + resize)
(function adjustContentTop() {
  function apply() {
    const header = document.querySelector(".news-header");
    const content = document.getElementById("content");
    if (header && content) {
      content.style.marginTop = header.offsetHeight + "px";
    }
  }
  window.addEventListener("load", apply);
  window.addEventListener("resize", apply);
})();

// Helper: prepare a panel for animated expand/collapse
function initAnimatedPanel(panel) {
  // Neutralize Bootstrap's .collapse display:none
  panel.style.display = "block";
  panel.style.overflow = "hidden";
  // If not already open, start closed
  if (panel.getAttribute("data-open") !== "true") {
    panel.style.maxHeight = "0px";
    panel.setAttribute("data-open", "false");
  }
  // Ensure transition is set (idempotent)
  if (!panel.style.transition) {
    panel.style.transition = "max-height 0.3s ease";
  }
}

document.addEventListener("DOMContentLoaded", function () {
  // Initialize all panels ('.news-comments .collapse')
  document.querySelectorAll(".news-comments .collapse").forEach(initAnimatedPanel);

  // Event delegation for all toggle links
  document.addEventListener("click", function (e) {
    const btn = e.target.closest(".toggle-comments");
    if (!btn) return;

    const wrapper = btn.closest(".news-comments");
    if (!wrapper) return;

    const panel = wrapper.querySelector(".collapse");
    if (!panel) return;

    // Make sure it's initialized (in case added dynamically)
    initAnimatedPanel(panel);

    const isOpen = panel.getAttribute("data-open") === "true";
    if (isOpen) {
      // Collapse
      // If panel height is 'auto' (none), measure then animate down
      if (panel.style.maxHeight === "none") {
        panel.style.maxHeight = panel.scrollHeight + "px";
        // force reflow
        void panel.offsetHeight;
      }
      panel.style.maxHeight = "0px";
      panel.setAttribute("data-open", "false");
      btn.setAttribute("aria-expanded", "false");
    } else {
      // Expand: measure content then animate up
      // Temporarily remove max-height to get natural height
      const prevTransition = panel.style.transition;
      panel.style.transition = "none";
      panel.style.maxHeight = "none";
      const target = panel.scrollHeight; // measure
      // force reflow
      void panel.offsetHeight;
      // restore transition and animate to measured height
      panel.style.transition = prevTransition || "max-height 0.3s ease";
      panel.style.maxHeight = target + "px";
      panel.setAttribute("data-open", "true");
      btn.setAttribute("aria-expanded", "true");

      // After animation completes, lock to 'auto' (none) so internal content can wrap/resize
      const onEnd = function (evt) {
        if (evt.propertyName === "max-height" && panel.getAttribute("data-open") === "true") {
          panel.style.transition = "none";
          panel.style.maxHeight = "none"; // behave like auto height
          // force reflow, then restore transition for future toggles
          void panel.offsetHeight;
          panel.style.transition = "max-height 0.3s ease";
          panel.removeEventListener("transitionend", onEnd);
        }
      };
      panel.addEventListener("transitionend", onEnd);
    }
  });
});
