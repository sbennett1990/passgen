module Password : sig
	type t

	(**
	 * Return the list of valid password characters
	 *)
	val valid_characters : char list

	(**
	 * Create a random password of the specified length
	 *)
	val generate_password : int -> t

	(**
	 * Print the password to stdout, followed by a newline
	 *)
	val print_password : t -> ()
end
