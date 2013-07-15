static void
<%=c_iterator%>(na_loop_t *const lp)
{
    size_t  i;
    char    *p1, *p2, *p3;
    ssize_t s1, s2, s3;
    size_t  *idx1, *idx2, *idx3;
    dtype    x, y;
    INIT_COUNTER(lp, i);
    INIT_PTR(lp, 0, p1, s1, idx1);
    INIT_PTR(lp, 1, p2, s2, idx2);
    INIT_PTR(lp, 2, p3, s3, idx3);
    if (idx1||idx2||idx3) {
        for (; i--;) {
            LOAD_DATA_STEP(p1, s1, idx1, dtype, x);
            LOAD_DATA_STEP(p2, s2, idx2, dtype, y);
            x = m_<%=op%>(x,y);
            STORE_DATA_STEP(p3, s3, idx3, dtype, x);
        }
    } else {
        for (; i--;) {
            x = *(dtype*)p1;
            p1+=s1;
            y = *(dtype*)p2;
            p2+=s2;
            x = m_<%=op%>(x,y);
            *(dtype*)p3 = x;
            p3+=s3;
        }
    }
}

/*
  Calculate a1 <%=op_map%> a2.
  @overload <%=op%>(a1,a2)
  @param [NArray,Numeric] a1  first value.
  @param [NArray,Numeric] a2  second value.
  @return [NArray::<%=class_name%>] <%=op%>(a1,a2).
*/
static VALUE
<%=c_singleton_method%>(VALUE mod, VALUE a1, VALUE a2)
{
    ndfunc_t *func;
    VALUE v;
    func = ndfunc_alloc(<%=c_iterator%>, FULL_LOOP,
                        2, 1, cT, cT, cT);
    v = ndloop_do(func, 2, a1, a2);
    ndfunc_free(func);
    return v;
}

/*
  Binary <%=op%>.
  @overload <%=op_map%> other
  @param [NArray,Numeric] other
  @return [NArray] <%=op%> of self and other.
*/
static VALUE
<%=c_instance_method%>(VALUE a1, VALUE a2)
{
    VALUE klass;
    klass = na_upcast(CLASS_OF(a1),CLASS_OF(a2));
    if (klass==cT) {
        return <%=c_singleton_method%>(cT,a1,a2);
    } else {
        return rb_funcall(klass,id_<%=op%>,2,a1,a2);
    }
}
