<?php
// Check functions exist first...
if(!function_exists('rijndael_encrypt') || !function_exists('rijndael_decrypt')) {
    throw new Exception('No Rijndael Module/Extension Installed');
}

// Encrypt all zeros, with 128 bit (16 charatcer key).
$buf = rijndael_encrypt('0000000000000000000000000000000', '0000000000000000000000000000000', 128);

// Dump encrypted buffer, without the trailing 6 bytes (unknown what these are... yet anyway.)
var_dump(substr($buf, 0, 16));

// Dump decrypted buffer, with the trailing 6 bytes...
var_dump(substr(rijndael_decrypt($buf, '00000000000000000000000000000000', 128), 0, 16));

?>
