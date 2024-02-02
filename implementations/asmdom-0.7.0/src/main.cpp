#include "asm-dom.hpp"
#include <emscripten/val.h>
#include <functional>
#include <string>
#include "view.hpp"
#include "model.hpp"

using namespace asmdom;

int i = 1;

Model model = {
        .entries = std::vector<Entry>(),
        .field = "",
        .uid = 0,
        .visibility = "All"
};

Entry oneEntry = {
        .description = "An Entry",
        .completed = true,
        .editing = false,
        .id = 1
};



VNode *current_view = nullptr;

bool Decrease(emscripten::val) {
    i--;

    view(model);
    return true;
}

bool Increase(emscripten::val) {
    i++;

    view(model);
    return true;
}

int main() {
    // Initialize asm-dom.
    asmdom::Config config = asmdom::Config();
    asmdom::init(config);

    // Replace <div id="root"/> by our virtual dom.
    emscripten::val document = emscripten::val::global("document");
    emscripten::val root = document.call<emscripten::val>("getElementById", std::string("root"));
    current_view = asmdom::h(u8"div", std::string(u8"Initial view"));
    asmdom::patch(root, current_view);

    // Build an example.
    model.entries.push_back(oneEntry);

    // Update the virtual dom.
    VNode* new_node = view(model);

    asmdom::patch(current_view, new_node);
    current_view = new_node;

    return 0;
};

