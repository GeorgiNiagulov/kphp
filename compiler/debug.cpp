// Compiler for PHP (aka KPHP)
// Copyright (c) 2020 LLC «V Kontakte»
// Distributed under the GPL v3 License, see LICENSE.notice.txt

#include "compiler/debug.h"

#include <string>
#include <vector>

#include "compiler/data/class-data.h"
#include "compiler/data/function-data.h"
#include "compiler/utils/string-utils.h"
#include "compiler/vertex.h"

static std::map<TokenType, std::string> TOKEN_TYPE_NAMES;
static std::map<Operation, std::string> OPERATION_NAMES;

void fillTokenTypeNames() {
  TOKEN_TYPE_NAMES[tok_empty] = "tok_empty";
  TOKEN_TYPE_NAMES[tok_int_const] = "tok_int_const";
  TOKEN_TYPE_NAMES[tok_float_const] = "tok_float_const";
  TOKEN_TYPE_NAMES[tok_null] = "tok_null";
  TOKEN_TYPE_NAMES[tok_nan] = "tok_nan";
  TOKEN_TYPE_NAMES[tok_inline_html] = "tok_inline_html";
  TOKEN_TYPE_NAMES[tok_str] = "tok_str";
  TOKEN_TYPE_NAMES[tok_str_begin] = "tok_str_begin";
  TOKEN_TYPE_NAMES[tok_str_end] = "tok_str_end";
  TOKEN_TYPE_NAMES[tok_expr_begin] = "tok_expr_begin";
  TOKEN_TYPE_NAMES[tok_expr_end] = "tok_expr_end";
  TOKEN_TYPE_NAMES[tok_var_name] = "tok_var_name";
  TOKEN_TYPE_NAMES[tok_func_name] = "tok_func_name";
  TOKEN_TYPE_NAMES[tok_while] = "tok_while";
  TOKEN_TYPE_NAMES[tok_for] = "tok_for";
  TOKEN_TYPE_NAMES[tok_foreach] = "tok_foreach";
  TOKEN_TYPE_NAMES[tok_if] = "tok_if";
  TOKEN_TYPE_NAMES[tok_else] = "tok_else";
  TOKEN_TYPE_NAMES[tok_elseif] = "tok_elseif";
  TOKEN_TYPE_NAMES[tok_break] = "tok_break";
  TOKEN_TYPE_NAMES[tok_continue] = "tok_continue";
  TOKEN_TYPE_NAMES[tok_echo] = "tok_echo";
  TOKEN_TYPE_NAMES[tok_dbg_echo] = "tok_dbg_echo";
  TOKEN_TYPE_NAMES[tok_var_dump] = "tok_var_dump";
  TOKEN_TYPE_NAMES[tok_function] = "tok_function";
  TOKEN_TYPE_NAMES[tok_varg] = "tok_varg";
  TOKEN_TYPE_NAMES[tok_array] = "tok_array";
  TOKEN_TYPE_NAMES[tok_tuple] = "tok_tuple";
  TOKEN_TYPE_NAMES[tok_shape] = "tok_shape";
  TOKEN_TYPE_NAMES[tok_as] = "tok_as";
  TOKEN_TYPE_NAMES[tok_case] = "tok_case";
  TOKEN_TYPE_NAMES[tok_switch] = "tok_switch";
  TOKEN_TYPE_NAMES[tok_class] = "tok_class";
  TOKEN_TYPE_NAMES[tok_interface] = "tok_interface";
  TOKEN_TYPE_NAMES[tok_trait] = "tok_trait";
  TOKEN_TYPE_NAMES[tok_extends] = "tok_extends";
  TOKEN_TYPE_NAMES[tok_implements] = "tok_implements";
  TOKEN_TYPE_NAMES[tok_namespace] = "tok_namespace";
  TOKEN_TYPE_NAMES[tok_use] = "tok_use";
  TOKEN_TYPE_NAMES[tok_const] = "tok_const";
  TOKEN_TYPE_NAMES[tok_default] = "tok_default";
  TOKEN_TYPE_NAMES[tok_do] = "tok_do";
  TOKEN_TYPE_NAMES[tok_eval] = "tok_eval";
  TOKEN_TYPE_NAMES[tok_return] = "tok_return";
  TOKEN_TYPE_NAMES[tok_list] = "tok_list";
  TOKEN_TYPE_NAMES[tok_include] = "tok_include";
  TOKEN_TYPE_NAMES[tok_include_once] = "tok_include_once";
  TOKEN_TYPE_NAMES[tok_require] = "tok_require";
  TOKEN_TYPE_NAMES[tok_require_once] = "tok_require_once";
  TOKEN_TYPE_NAMES[tok_print] = "tok_print";
  TOKEN_TYPE_NAMES[tok_unset] = "tok_unset";
  TOKEN_TYPE_NAMES[tok_var] = "tok_var";
  TOKEN_TYPE_NAMES[tok_global] = "tok_global";
  TOKEN_TYPE_NAMES[tok_static] = "tok_static";
  TOKEN_TYPE_NAMES[tok_final] = "tok_final";
  TOKEN_TYPE_NAMES[tok_abstract] = "tok_abstract";
  TOKEN_TYPE_NAMES[tok_goto] = "tok_goto";
  TOKEN_TYPE_NAMES[tok_isset] = "tok_isset";
  TOKEN_TYPE_NAMES[tok_declare] = "tok_declare";
  TOKEN_TYPE_NAMES[tok_eq1] = "tok_eq1";
  TOKEN_TYPE_NAMES[tok_eq2] = "tok_eq2";
  TOKEN_TYPE_NAMES[tok_eq3] = "tok_eq3";
  TOKEN_TYPE_NAMES[tok_lt] = "tok_lt";
  TOKEN_TYPE_NAMES[tok_gt] = "tok_gt";
  TOKEN_TYPE_NAMES[tok_le] = "tok_le";
  TOKEN_TYPE_NAMES[tok_ge] = "tok_ge";
  TOKEN_TYPE_NAMES[tok_spaceship] = "tok_spaceship";
  TOKEN_TYPE_NAMES[tok_neq2] = "tok_neq2";
  TOKEN_TYPE_NAMES[tok_neq3] = "tok_neq3";
  TOKEN_TYPE_NAMES[tok_neq_lg] = "tok_neq_lg";
  TOKEN_TYPE_NAMES[tok_oppar] = "tok_oppar";
  TOKEN_TYPE_NAMES[tok_clpar] = "tok_clpar";
  TOKEN_TYPE_NAMES[tok_opbrc] = "tok_opbrc";
  TOKEN_TYPE_NAMES[tok_clbrc] = "tok_clbrc";
  TOKEN_TYPE_NAMES[tok_opbrk] = "tok_opbrk";
  TOKEN_TYPE_NAMES[tok_clbrk] = "tok_clbrk";
  TOKEN_TYPE_NAMES[tok_semicolon] = "tok_semicolon";
  TOKEN_TYPE_NAMES[tok_comma] = "tok_comma";
  TOKEN_TYPE_NAMES[tok_dot] = "tok_dot";
  TOKEN_TYPE_NAMES[tok_colon] = "tok_colon";
  TOKEN_TYPE_NAMES[tok_at] = "tok_at";
  TOKEN_TYPE_NAMES[tok_pow] = "tok_pow";
  TOKEN_TYPE_NAMES[tok_inc] = "tok_inc";
  TOKEN_TYPE_NAMES[tok_dec] = "tok_dec";
  TOKEN_TYPE_NAMES[tok_plus] = "tok_plus";
  TOKEN_TYPE_NAMES[tok_minus] = "tok_minus";
  TOKEN_TYPE_NAMES[tok_times] = "tok_times";
  TOKEN_TYPE_NAMES[tok_divide] = "tok_divide";
  TOKEN_TYPE_NAMES[tok_mod] = "tok_mod";
  TOKEN_TYPE_NAMES[tok_and] = "tok_and";
  TOKEN_TYPE_NAMES[tok_or] = "tok_or";
  TOKEN_TYPE_NAMES[tok_xor] = "tok_xor";
  TOKEN_TYPE_NAMES[tok_not] = "tok_not";
  TOKEN_TYPE_NAMES[tok_log_not] = "tok_log_not";
  TOKEN_TYPE_NAMES[tok_question] = "tok_question";
  TOKEN_TYPE_NAMES[tok_null_coalesce] = "tok_null_coalesce";
  TOKEN_TYPE_NAMES[tok_leq] = "tok_leq";
  TOKEN_TYPE_NAMES[tok_shl] = "tok_shl";
  TOKEN_TYPE_NAMES[tok_geq] = "tok_geq";
  TOKEN_TYPE_NAMES[tok_shr] = "tok_shr";
  TOKEN_TYPE_NAMES[tok_neq] = "tok_neq";
  TOKEN_TYPE_NAMES[tok_set_add] = "tok_set_add";
  TOKEN_TYPE_NAMES[tok_set_sub] = "tok_set_sub";
  TOKEN_TYPE_NAMES[tok_set_mul] = "tok_set_mul";
  TOKEN_TYPE_NAMES[tok_set_div] = "tok_set_div";
  TOKEN_TYPE_NAMES[tok_set_mod] = "tok_set_mod";
  TOKEN_TYPE_NAMES[tok_set_pow] = "tok_set_pow";
  TOKEN_TYPE_NAMES[tok_set_and] = "tok_set_and";
  TOKEN_TYPE_NAMES[tok_log_and] = "tok_log_and";
  TOKEN_TYPE_NAMES[tok_log_and_let] = "tok_log_and_let";
  TOKEN_TYPE_NAMES[tok_set_or] = "tok_set_or";
  TOKEN_TYPE_NAMES[tok_log_or] = "tok_log_or";
  TOKEN_TYPE_NAMES[tok_log_or_let] = "tok_log_or_let";
  TOKEN_TYPE_NAMES[tok_set_xor] = "tok_set_xor";
  TOKEN_TYPE_NAMES[tok_log_xor] = "tok_log_xor";
  TOKEN_TYPE_NAMES[tok_log_xor_let] = "tok_log_xor_let";
  TOKEN_TYPE_NAMES[tok_set_shr] = "tok_set_shr";
  TOKEN_TYPE_NAMES[tok_set_shl] = "tok_set_shl";
  TOKEN_TYPE_NAMES[tok_set_dot] = "tok_set_dot";
  TOKEN_TYPE_NAMES[tok_double_arrow] = "tok_double_arrow";
  TOKEN_TYPE_NAMES[tok_double_colon] = "tok_double_colon";
  TOKEN_TYPE_NAMES[tok_arrow] = "tok_arrow";
  TOKEN_TYPE_NAMES[tok_class_c] = "tok_class_c";
  TOKEN_TYPE_NAMES[tok_file_c] = "tok_file_c";
  TOKEN_TYPE_NAMES[tok_func_c] = "tok_func_c";
  TOKEN_TYPE_NAMES[tok_dir_c] = "tok_dir_c";
  TOKEN_TYPE_NAMES[tok_line_c] = "tok_line_c";
  TOKEN_TYPE_NAMES[tok_method_c] = "tok_method_c";
  TOKEN_TYPE_NAMES[tok_namespace_c] = "tok_namespace_c";
  TOKEN_TYPE_NAMES[tok_int] = "tok_int";
  TOKEN_TYPE_NAMES[tok_float] = "tok_float";
  TOKEN_TYPE_NAMES[tok_string] = "tok_string";
  TOKEN_TYPE_NAMES[tok_object] = "tok_object";
  TOKEN_TYPE_NAMES[tok_callable] = "tok_callable";
  TOKEN_TYPE_NAMES[tok_bool] = "tok_bool";
  TOKEN_TYPE_NAMES[tok_void] = "tok_void";
  TOKEN_TYPE_NAMES[tok_mixed] = "tok_mixed";
  TOKEN_TYPE_NAMES[tok_conv_int] = "tok_conv_int";
  TOKEN_TYPE_NAMES[tok_conv_float] = "tok_conv_float";
  TOKEN_TYPE_NAMES[tok_conv_string] = "tok_conv_string";
  TOKEN_TYPE_NAMES[tok_conv_array] = "tok_conv_array";
  TOKEN_TYPE_NAMES[tok_conv_object] = "tok_conv_object";
  TOKEN_TYPE_NAMES[tok_conv_bool] = "tok_conv_bool";
  TOKEN_TYPE_NAMES[tok_conv_var] = "tok_conv_var";
  TOKEN_TYPE_NAMES[tok_conv_uint] = "tok_conv_uint";
  TOKEN_TYPE_NAMES[tok_conv_long] = "tok_conv_long";
  TOKEN_TYPE_NAMES[tok_conv_ulong] = "tok_conv_ulong";
  TOKEN_TYPE_NAMES[tok_false] = "tok_false";
  TOKEN_TYPE_NAMES[tok_true] = "tok_true";
  TOKEN_TYPE_NAMES[tok_define] = "tok_define";
  TOKEN_TYPE_NAMES[tok_defined] = "tok_defined";
  TOKEN_TYPE_NAMES[tok_triple_colon] = "tok_triple_colon";
  TOKEN_TYPE_NAMES[tok_triple_gt] = "tok_triple_gt";
  TOKEN_TYPE_NAMES[tok_triple_lt] = "tok_triple_lt";
  TOKEN_TYPE_NAMES[tok_throw] = "tok_throw";
  TOKEN_TYPE_NAMES[tok_new] = "tok_new";
  TOKEN_TYPE_NAMES[tok_Exception] = "tok_Exception";
  TOKEN_TYPE_NAMES[tok_try] = "tok_try";
  TOKEN_TYPE_NAMES[tok_catch] = "tok_catch";
  TOKEN_TYPE_NAMES[tok_public] = "tok_public";
  TOKEN_TYPE_NAMES[tok_private] = "tok_private";
  TOKEN_TYPE_NAMES[tok_protected] = "tok_protected";
  TOKEN_TYPE_NAMES[tok_phpdoc] = "tok_phpdoc";
  TOKEN_TYPE_NAMES[tok_clone] = "tok_clone";
  TOKEN_TYPE_NAMES[tok_instanceof] = "tok_instanceof";
  TOKEN_TYPE_NAMES[tok_end] = "tok_end";

  // this assert will fail whether new TokenType entry is added;
  // how to fix: add TOKEN_TYPE_NAMES[$newtok] = "$newtok" to the block above
  kphp_assert((TOKEN_TYPE_NAMES.size()-1) == tok_end);
}

void fillOperationNames() {
#define FOREACH_OP(x) OPERATION_NAMES[x] = #x;

#include "auto/compiler/vertex/foreach-op.h"
}


std::string debugTokenName(TokenType t) {
  if (TOKEN_TYPE_NAMES.empty()) {
    fillTokenTypeNames();
  }

  return TOKEN_TYPE_NAMES[t];
}

std::string debugOperationName(Operation o) {
  if (OPERATION_NAMES.empty()) {
    fillOperationNames();
  }

  return OPERATION_NAMES[o];
}


std::string debugVertexMore(VertexPtr v) {
  switch (v->type()) {
    case op_alloc:
      return "new " + v.as<op_alloc>()->allocated_class_name;
    case op_func_call:
      return string(v->extra_type == op_ex_func_call_arrow ? "->" : "") + v->get_string() + "()";
    case op_func_name:
      return v->get_string();
    case op_function:
      return v.as<op_function>()->func_id->name + "()";
    case op_var:
      return "$" + v->get_string();
    case op_instance_prop:
      return "...->" + v->get_string();
    case op_string:
      return v->get_string() == "\n" ? "\"\\n\"" : "\"" + v->get_string() + "\"";
    case op_int_const:
      return v->get_string();
    case op_type_expr_class:
      return v.as<op_type_expr_class>()->class_ptr
             ? v.as<op_type_expr_class>()->class_ptr->name : "class_ptr = null";
    case op_type_expr_type:
      return ptype_name(v->type_help);
    case op_seq:
      return std::to_string(v->size());
    case op_type_expr_arg_ref:
      return "^" + std::to_string(v.as<op_type_expr_arg_ref>()->int_val);
    case op_phpdoc_raw:
      return "/*" + std::string(v.as<op_phpdoc_raw>()->phpdoc_str) + "*/";
    default:
      return "";
  }
}

void debugPrintVertexTree(VertexPtr root, int level) {
  for (int i = 0; i < level; ++i) {
    fmt_print("  ");
  }
  fmt_print("{} {}\n", debugOperationName(root->type()), debugVertexMore(root));

  for (auto i : *root) {
    debugPrintVertexTree(i, level + 1);
  }
}

void debugPrintFunction(FunctionPtr function) {
  fmt_print("--- {}\n", function->name);
  debugPrintVertexTree(function->root, 0);
}


struct GdbVertex {
  Operation type;
  std::string str;

  GdbVertex *ith0;
  GdbVertex *ith1;
  GdbVertex *ith2;
};

GdbVertex *debugVertexToGdb(VertexPtr v) {
  GdbVertex *g = new GdbVertex;
  int size = v ? v->size() : 0;

  g->type = (v ? v->type() : meta_op_base);
  g->str = v ? debugVertexMore(v) : "";
  VertexRange sons{v->begin(), v->end()};
  g->ith0 = size > 0 ? debugVertexToGdb(sons[0]) : nullptr;
  g->ith1 = size > 1 ? debugVertexToGdb(sons[1]) : nullptr;
  g->ith2 = size > 2 ? debugVertexToGdb(sons[2]) : nullptr;

  return g;
}

// "expr*8" in CLion debugger
GdbVertex operator*(VertexPtr v, int n __attribute__((unused))) {
  return *debugVertexToGdb(v);
}

