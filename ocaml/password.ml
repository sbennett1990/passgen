module Password = struct
	type t = char list

	(* ASCII Character Codes for Passwords *)
	let character_codes = [
		(* Numbers *)
		48; 49; 50; 51; 52; 53; 54; 55; 56; 57;
		(* Uppercase Letters *)
		65; 66; 67; 68; 69; 70; 71; 72; 73; 74; 75; 76; 77; 78; 79; 80; 81; 82;
		83; 84; 85; 86; 87; 88; 89; 90;
		(* Lowercase Letters *)
		97; 98; 99; 100; 102; 103; 104; 105; 106; 107; 108; 109; 110; 111; 112;
		113; 114; 115; 116; 117; 118; 119; 120; 121; 122;
		(* Special Characters *)
		33; 35; 36; 37; 38; 42; 43; 45; 47; 58; 59; 60; 61; 62; 63; 64; 91; 93;
		94
	]

	let upper_bound = List.length character_codes

	let random_character () =
		let i = Random.int upper_bound in
		Char.chr (List.nth character_codes i)

	let valid_characters =
		List.map Char.chr character_codes

	let switch_case c =
		let lower_c = Char.lowercase_ascii c in
		if c <> lower_c then
			lower_c
		else
			Char.uppercase_ascii c

	let random_case c =
		if Random.bool () then
			switch_case c
		else
			c

	let generate_password size =
		let rec create list n =
			if n < 1 then
				list
			else
				let c = random_character () in
				create (c::list) (n - 1)
		in
		if size < 1 then
			[]
		else
			let passwd = create [] size in
			List.map random_case passwd

	let print_password passwd =
		List.iter print_char passwd;
		print_newline ()
end
