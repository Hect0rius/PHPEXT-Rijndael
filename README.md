# PHPEXT-Rijndael
This PHP extension has been built to aid none IV supported encryption/decryption from within PHP itself., It uses the Rijndael code from abgx360 tool.

# [ Basic Usage ]
There are 2 functions, rijndael_encrypt and rijndael_decrypt, They do not support IV's, this is the original code before 
it became AES.

the usage is as followed :

rijndael_encrypt(string plainText, string key, long keyBits);

rijndael_decrypt(string ciphered, string key, long keyBits);

The following keyBits/KeySize

128 = 16 character key.

192 = 24 character key.

256 = 32 character key.

# [ Notes ]
There is currently a error within the code somewhere, as I am new to writing extensions (my first one) I have noticed it will
encrypt and decrypt correctly however it adds padding onto the end of the string, since it should only accept a 16 character string, simply use substr to amend the extra padding, for more information checkout : https://stackoverflow.com/questions/44591397/building-a-php-extension-using-original-rijndael-correct-encryption-decrypt-how
Big thanks to zaph for their advice.


# [ Installing ]
- Linux/Ubuntu (PHP-FPM/PHP-CLI):
You will need to install a few tools firstly, the command : "sudo apt-get install php7.0-fpm php7.0-cli php7.0-dev"

then simply git clone the directory via "git clone https://github.com/Hect0rius/PHPEXT-Rijndael.git" 

Then change the directory : "PHPEXT-Rijndael", then type the following command to initialise it for compiling "phpize".

Then proceed to configure it via "./configure --enable-rijndael", you then want to run "make", then install it via "sudo make install".

After the building phaze is complete, it will output the directory that the .so is located in... Mine looked like the below :
"Installing shared extensions:     /usr/lib/php/20151012/"

Simply copy this directory "/usr/lib/php/20151012/" from the terminal/console, then cd directory to the /etc/php folder like so :
"cd /etc/php/7.0/cli_or_fpm/conf.d/" (change for cli or fpm.)

Then as a example, copy one of the already made config files, I choose ftp...

"sudo cp 20-ftp.ini 20-rijndael.ini" then nano into it and change the extension=ftp.so to (with your previous directory)

extension=/usr/lib/php/20151012/rijndael.so.

"sudo nano 20-rijndael.ini" then press Ctrl-X then Y and enter to save it.

for cli it should now work, just executable the test.php file via "php -f test.php"

for fpm, simply restart the daemon via "sudo service php7.0-fpm reload/restart"

# [ Author ]
PHP Extension : Hect0r Xorius <staticpi.net@gmail.com> - StaticPi.net

Rijndael : 
           Vincent Rijmen <vincent.rijmen@esat.kuleuven.ac.be>

           Antoon Bosselaers <antoon.bosselaers@esat.kuleuven.ac.be>
           
           Paulo Barreto <paulo.barreto@terra.com.br>
           
 # [ With Thanks ]
 Team-Xecuter, Se7ensins, ABGX360 (All the Staff and Developers)
