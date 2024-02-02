#include "asm-dom.hpp"
#include <emscripten/val.h>
#include <functional>
#include <string>

using namespace asmdom;

void Render();

VNode *current_view = nullptr;
int i = 1;

bool Decrease(emscripten::val) {
    i--;

    Render();
    return true;
}

bool Increase(emscripten::val) {
    i++;

    Render();
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


int main() {
    // Initialize asm-dom.
    Config config = Config();
    init(config);

    // Replace <div id="root"/> by our virtual dom.
    emscripten::val document = emscripten::val::global("document");
    emscripten::val root = document.call<emscripten::val>("getElementById", std::string("root"));
    current_view = h(u8"div", std::string(u8"Initial view"));
    patch(root, current_view);

    // Update the virtual dom.
    Render();

    return 0;
};


// Render the view (i.e. replace the main virtual dom).
void Render() {
    // The main view.
    VNode *new_node =


            h(u8"div", Data(Attrs{{u8"id",    u8"root"},
                                  {u8"class", u8"todomvc-wrapper"}}),
              h(u8"section", Data(Attrs{{u8"class", u8"todoapp"}}),
                Children{h(u8"!", std::string(u8" viewInput ")),
                         h(u8"header",
                           Data(
                                   Attrs{
                                           {u8"class",
                                            u8"header"}}),
                           Children{
                                   h(
                                           u8"h1",
                                           std::string(
                                                   u8"todos")),
                                   h(
                                           u8"input",
                                           Data(
                                                   Attrs{{u8"class",       u8"new-todo"},
                                                         {u8"placeholder", u8"What needs to be done?"},
                                                         {u8"autofocus",   u8"true"},
                                                         {u8"name",        u8"newTodo"}},
                                                   Props{
                                                           {u8"value",
                                                            emscripten::val(
                                                                    std::wstring(
                                                                            L"All"))}}))}),
                         h(u8"!", std::string(u8" viewEntries ")),
                         h(u8"section",
                           Data(Attrs{{u8"class", u8"main"}}),
                           Children{h(u8"input", Data(
                                   Attrs{{u8"class", u8"toggle-all"},
                                         {u8"type",  u8"checkbox"},
                                         {u8"name",  u8"toggle"}})),
                                    h(u8"label", Data(
                                              Attrs{
                                                      {u8"for", u8"toggle-all"}}),
                                      std::string(
                                              u8"Mark all as complete")),
                                    h(u8"ul",
                                      h(u8"li",
                                        Data(
                                                Attrs{
                                                        {u8"class",
                                                         u8"completed editing"}}),
                                        Children{
                                                h(
                                                        u8"div",
                                                        Data(
                                                                Attrs{
                                                                        {u8"class",
                                                                         u8"view"}}),
                                                        Children{
                                                                h(
                                                                        u8"input",
                                                                        Data(
                                                                                Attrs{{u8"class", u8"toggle"},
                                                                                      {u8"type",  u8"checkbox"}})),
                                                                h(
                                                                        u8"label",
                                                                        std::string(
                                                                                u8"todo description")),
                                                                h(
                                                                        u8"button",
                                                                        Data(
                                                                                Attrs{
                                                                                        {u8"class",
                                                                                         u8"destroy"}}))}),
                                                h(
                                                        u8"input",
                                                        Data(
                                                                Attrs{{u8"class", u8"edit"},
                                                                      {u8"name",  u8"title"},
                                                                      {u8"id",    u8"todo-1"}},
                                                                Props{
                                                                        {u8"value",
                                                                         emscripten::val(
                                                                                 std::wstring(
                                                                                         L"todo description"))}}))}))}),
                         h(u8"!", std::string(u8" viewControls ")),
                         h(u8"footer", Data(
                                 Attrs{{u8"class",  u8"footer"},
                                       {u8"hidden", u8"false"}}))}));

    patch(current_view, new_node);
    current_view = new_node;
}