type token = { str : string; offset : int; }
type t
val create : string -> t
val parse : t -> string -> token list
