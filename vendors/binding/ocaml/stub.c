#include <friso/friso.h>
#include <string.h>
#include <stdio.h>

#define CAML_NAME_SPACE
#include <caml/mlvalues.h>
#include <caml/alloc.h>
#include <caml/memory.h>
#include <caml/fail.h>
#include <caml/callback.h>
#include <caml/custom.h>
#include <caml/intext.h>
#include <caml/threads.h>

#define p_val(v) (*(ptrdiff_t*)Data_custom_val(v))

#define c_string_val(v) (*(char* *)Data_custom_val(v))

#define t_val(v) (*(friso_t*)Data_custom_val(v))
#define config_val(v) (*(friso_config_t*)Data_custom_val(v))
#define task_val(v) (*(friso_task_t*)Data_custom_val(v))

static intnat p_hash_op(value v) {
    return (intnat)p_val(v);
}

static int p_comp_op(value v1, value v2) {
    return p_val(v1) - p_val(v2);
}

// c_string {
    void cs_free_op(value cs) {
        free(*(char**)Data_custom_val(cs));
        return;
    }

    struct custom_operations cs_ops= {
        "org.machinelife.ocaml.friso.cs_ops",
        cs_free_op,
        p_comp_op,
        p_hash_op,
        NULL,
        NULL,
        NULL,
    };
// }

// t {
    void t_free_op(value t) {
        friso_free(t_val(t));
        return;
    }

    struct custom_operations t_ops= {
        "org.machinelife.ocaml.friso.t_ops",
        t_free_op,
        p_comp_op,
        p_hash_op,
        NULL,
        NULL,
        NULL,
    };
// }

// config {
    void config_free_op(value config) {
        friso_free_config(config_val(config));
        return;
    }

    struct custom_operations config_ops= {
        "org.machinelife.ocaml.friso.config_ops",
        config_free_op,
        p_comp_op,
        p_hash_op,
        NULL,
        NULL,
        NULL,
    };
// }

// task {
    void task_free_op(value task) {
        friso_free_task(task_val(task));
        return;
    }

    struct custom_operations task_ops= {
        "org.machinelife.ocaml.friso.task_ops",
        task_free_op,
        p_comp_op,
        p_hash_op,
        NULL,
        NULL,
        NULL,
    };
// }

CAMLprim value to_c_string_stub(value str) {
    CAMLparam1(str);
    CAMLlocal1(result);
    result= caml_alloc_custom(&cs_ops, sizeof(char*), 0,0);
    c_string_val(result)= strdup(String_val(str));
    CAMLreturn(result);
}

CAMLprim value friso_new_stub(value unit) {
    CAMLparam1(unit);
    CAMLlocal1(result);
    result= caml_alloc_custom(&t_ops, sizeof(friso_t), 0,0);
    t_val(result)= friso_new();
    CAMLreturn(result);
}

CAMLprim value friso_new_config_stub(value unit) {
    CAMLparam1(unit);
    CAMLlocal1(result);
    result= caml_alloc_custom(&config_ops, sizeof(friso_config_t), 0,0);
    config_val(result)= friso_new_config();
    CAMLreturn(result);
}

CAMLprim value friso_new_task_stub(value unit) {
    CAMLparam1(unit);
    CAMLlocal1(result);
    result= caml_alloc_custom(&task_ops, sizeof(friso_task_t), 0,0);
    task_val(result)= friso_new_task();
    CAMLreturn(result);
}

CAMLprim value friso_init_from_ifile_stub(value t, value config, value path) {
    CAMLparam3(t, config, path);
    friso_init_from_ifile(t_val(t), config_val(config), String_val(path));
    CAMLreturn(Val_unit);
}

CAMLprim value set_text_stub(value task, value str) {
    CAMLparam2(task, str);
    friso_set_text(task_val(task), c_string_val(str));
    CAMLreturn(Val_unit);
}

CAMLprim value friso_next_token_stub(value t, value config, value task) {
    CAMLparam3(t, config, task);
    CAMLlocal2(result, token);
    friso_t friso= t_val(t);
    friso_config_t friso_config= config_val(config);
    friso_task_t friso_task= task_val(task);
    if (friso_config->next_token(friso, friso_config, friso_task) != NULL) {
        result= caml_alloc(1, 0);
        token= caml_alloc(2, 0);
        Store_field(token, 0, caml_copy_string(friso_task->token->word));
        Store_field(token, 1, Val_int(friso_task->token->offset));
        Store_field(result, 0, token);
    } else {
        result= Val_int(0);
    }
    
    CAMLreturn(result);
}

