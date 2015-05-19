type token= {
  str: string;
  offset: int;
}

module C = struct
  type t
  type config
  type task
  type c_string
  type task_str= {
    task: task;
    str: c_string
  }

  external create: unit -> t= "friso_new_stub"
  external create_config: unit -> config= "friso_new_config_stub"
  external create_task: unit -> task= "friso_new_task_stub"

  external t_init_from_ifile: t -> config -> string -> unit= "friso_init_from_ifile_stub"

  external to_c_string: string -> c_string= "to_c_string_stub"

  external set_text: task -> c_string -> unit= "set_text_stub"
  let set_text task str=
    let str= to_c_string str in
    set_text task str;
    {task; str}

  external next_token: t -> config -> task -> token option= "friso_next_token_stub"
  let next_token t config task=
    next_token t config task.task
end

type t= {
  friso: C.t;
  config: C.config;
}

let create configFile=
  let friso= C.create ()
  and config= C.create_config () in
  C.t_init_from_ifile friso config configFile;
  {friso; config}

let parse t text=
  let task= C.(set_text (create_task ()) text) in
  let rec parse ()=
    match C.next_token t.friso t.config task with
    | Some str -> str :: parse ()
    | None -> []
  in
  parse ()

