(**
 * Create a password of specified length, filled with random ASCII characters
 *)
val generate_password : int -> char list

(** Print the password to stdout, followed by a newline *)
val print_password : char list -> ()
