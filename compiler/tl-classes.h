// Compiler for PHP (aka KPHP)
// Copyright (c) 2020 LLC «V Kontakte»
// Distributed under the GPL v3 License, see LICENSE.notice.txt

#pragma once

#include "common/tl2php/php-classes.h"
#include "common/tlo-parsing/tlo-parsing-tools.h"

#include "compiler/data/data_ptr.h"

class TlClasses {
public:
  static bool new_tl_long;

  void load_from(const std::string &tlo_schema, bool generate_tl_internals);

  const std::unique_ptr<const vk::tl::tl_scheme> &get_scheme() const { return scheme_; }
  const vk::tl::PhpClasses &get_php_classes() const { return php_classes_; }

private:
  std::unique_ptr<const vk::tl::tl_scheme> scheme_;
  vk::tl::PhpClasses php_classes_;
};
