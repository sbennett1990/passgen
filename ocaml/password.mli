(** An ASCII character password *)
type t

(**
 * Create a password of specified length, filled with random ASCII characters
 *)
val generate_password : int -> t

(** Print the password to stdout, followed by a newline *)
val print_password : t -> ()
