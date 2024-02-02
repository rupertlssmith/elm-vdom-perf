#include "asm-dom.hpp"
#include <emscripten/val.h>
#include <functional>
#include <string>
#include "view.hpp"

using namespace asmdom;

int i = 1;

bool Decrease(emscripten::val) {
    i--;

    view();
    return true;
}

bool Increase(emscripten::val) {
    i++;

    view();
    return true;
}

// State.
struct Entry {
    std::string description;
    bool completed;
    bool editing;
    int id;
};

struct Model {
    std::vector<Entry> entries;
    std::string field;
    int uid;
    std::string visibility;
};

Model model = {
        .entries = std::vector<Entry>(),
        .field = "",
        .uid = 0,
        .visibility = "All"
};

VNode *current_view = nullptr;

int main() {
    // Initialize asm-dom.
    asmdom::Config config = asmdom::Config();
    asmdom::init(config);

    // Replace <div id="root"/> by our virtual dom.
    emscripten::val document = emscripten::val::global("document");
    emscripten::val root = document.call<emscripten::val>("getElementById", std::string("root"));
    current_view = asmdom::h(u8"div", std::string(u8"Initial view"));
    asmdom::patch(root, current_view);

    // Update the virtual dom.
    VNode* new_node = view();

    asmdom::patch(current_view, new_node);
    current_view = new_node;

    return 0;
};

