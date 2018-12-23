#pragma once

#include "compiler/data/data_ptr.h"
#include "compiler/threading/data-stream.h"
#include "compiler/threading/hash-table.h"

class SortAndInheritClassesF {
  struct wait_list {
    bool done;
    vector<ClassPtr> waiting;
  };

  TSHashTable<wait_list> ht;

  void on_class_ready(ClassPtr klass, DataStream<FunctionPtr> &function_stream);

  VertexPtr generate_function_with_parent_call(VertexAdaptor<op_function> root, ClassPtr parent_class, ClassPtr child_class, const string &local_name);

  void inherit_child_class_from_parent(ClassPtr child_class, ClassPtr parent_class, DataStream<FunctionPtr> &function_stream);
  void inherit_static_method_from_parent(ClassPtr child_class, ClassPtr parent_class, const string &local_name, DataStream<FunctionPtr> &function_stream);

  pair<bool, std::string> is_class_ready(ClassPtr klass);

public:
  void execute(ClassPtr klass, MultipleDataStreams<FunctionPtr, ClassPtr> &os);
};
