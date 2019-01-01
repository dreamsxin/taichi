#include "tlang.h"

TLANG_NAMESPACE_BEGIN

Expr &Expr::operator=(const Expr &o) {
  // TC_ASSERT(allow_store);
  if (!allow_store || !node || node->type != NodeType::pointer) {
    // Expr assignment
    node = o.node;
  } else {
    // store to pointed addr
    TC_ASSERT(node->type == NodeType::pointer);
    auto &prog = get_current_program();
    // TC_ASSERT(&prog != nullptr);
    // TC_ASSERT(node->get_address().initialized());
    prog.store(*this, load_if_pointer(o));
  }
  return *this;
}

Expr Expr::operator[](const Expr &i) {
  TC_ASSERT(i);
  TC_ASSERT(node->type == NodeType::addr);
  TC_ASSERT(i->type == NodeType::index || i->data_type == DataType::i32);
  return create(NodeType::pointer, *this, i);
}

void *Expr::evaluate_addr(int i) {
  TC_ASSERT(node->new_address);
  return node->new_address->evaluate(i);
}

bool Expr::allow_store = false;
// assignment should not be used outside function definition; use "Expr::set"
// instead

TLANG_NAMESPACE_END
