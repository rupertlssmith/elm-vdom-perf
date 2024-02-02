#include "asm-dom.hpp"
#include <emscripten/val.h>
#include <functional>
#include <string>

void Render();
asmdom::VNode *current_view = nullptr;
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
  asmdom::Config config = asmdom::Config();
  asmdom::init(config);

  // Replace <div id="root"/> by our virtual dom.
  emscripten::val document = emscripten::val::global("document");
  emscripten::val root = document.call<emscripten::val>("getElementById", std::string("root"));
  current_view = asmdom::h(u8"div", std::string(u8"Initial view"));
  asmdom::patch(root, current_view);

  // Update the virtual dom.
  Render();

  return 0;
};


// Render the view (i.e. replace the main virtual dom).
void Render() {
  // The main view.
  asmdom::VNode* new_node =
    /*asmdom::h(u8"div", asmdom::Data (asmdom::Attrs {{u8"id", u8"root"}}), asmdom::Children {asmdom::h(u8"h1", std::string(u8"This interface has been written in C++!")), asmdom::h(u8"div", asmdom::Data (asmdom::Attrs {{u8"class", u8"button_container"}}), asmdom::Children {asmdom::h(u8"a", asmdom::Data (asmdom::Attrs {{u8"class", u8"button"}}, asmdom::Callbacks {{u8"onclick", Decrease}}), std::string(u8"Decrease")), asmdom::h(u8"a", asmdom::Data (asmdom::Attrs {{u8"class", u8"button"}}, asmdom::Callbacks {{u8"onclick", Increase}}), std::string(u8"Increase"))}), asmdom::h(u8"div", asmdom::Data (asmdom::Attrs {{u8"class", u8"display_i"}}), u8"i = " + std::string(std::to_string(i))), asmdom::h(u8"div", asmdom::Data (asmdom::Attrs {{u8"class", u8"action_list"}}), action_list)});*/
    
    asmdom::h(u8"div", asmdom::Data (asmdom::Attrs {{u8"id", u8"root"}, {u8"class", u8"todomvc-wrapper"}}), asmdom::h(u8"section", asmdom::Data (asmdom::Attrs {{u8"class", u8"todoapp"}}), asmdom::Children {asmdom::h(u8"!", std::string(u8" viewInput ")), asmdom::h(u8"header", asmdom::Data (asmdom::Attrs {{u8"class", u8"header"}}), asmdom::Children {asmdom::h(u8"h1", std::string(u8"todos")), asmdom::h(u8"input", asmdom::Data (asmdom::Attrs {{u8"class", u8"new-todo"}, {u8"placeholder", u8"What needs to be done?"}, {u8"autofocus", u8"true"}, {u8"name", u8"newTodo"}}, asmdom::Props {{u8"value", emscripten::val(std::wstring(L"All"))}}))}), asmdom::h(u8"!", std::string(u8" viewEntries ")), asmdom::h(u8"section", asmdom::Data (asmdom::Attrs {{u8"class", u8"main"}}), asmdom::Children {asmdom::h(u8"input", asmdom::Data (asmdom::Attrs {{u8"class", u8"toggle-all"}, {u8"type", u8"checkbox"}, {u8"name", u8"toggle"}})), asmdom::h(u8"label", asmdom::Data (asmdom::Attrs {{u8"for", u8"toggle-all"}}), std::string(u8"Mark all as complete")), asmdom::h(u8"ul", asmdom::h(u8"li", asmdom::Data (asmdom::Attrs {{u8"class", u8"completed editing"}}), asmdom::Children {asmdom::h(u8"div", asmdom::Data (asmdom::Attrs {{u8"class", u8"view"}}), asmdom::Children {asmdom::h(u8"input", asmdom::Data (asmdom::Attrs {{u8"class", u8"toggle"}, {u8"type", u8"checkbox"}})), asmdom::h(u8"label", std::string(u8"todo description")), asmdom::h(u8"button", asmdom::Data (asmdom::Attrs {{u8"class", u8"destroy"}}))}), asmdom::h(u8"input", asmdom::Data (asmdom::Attrs {{u8"class", u8"edit"}, {u8"name", u8"title"}, {u8"id", u8"todo-1"}}, asmdom::Props {{u8"value", emscripten::val(std::wstring(L"todo description"))}}))}))}), asmdom::h(u8"!", std::string(u8" viewControls ")), asmdom::h(u8"footer", asmdom::Data (asmdom::Attrs {{u8"class", u8"footer"}, {u8"hidden", u8"false"}}))}));

  asmdom::patch(current_view, new_node);
  current_view = new_node;
}