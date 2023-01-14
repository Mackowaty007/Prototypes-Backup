<?php
$servername = "127.0.0.1";
$username = "root";
$password = "";
$dbname = "baza";

echo ("laczenie z baza danych<br>");
$baza = mysqli_connect($servername, $username, $password, $dbname);
if (!$baza){
    die("nie idzie sie kurde poloczyc<br>");
}
echo ("polaczono<br>");

$zapytanie = mysqli_query("SELECT * FROM pracownicy");
echo (mysqli_fetch_row($zapytanie));

echo ("Dodano rezerwacje do bazy<br>");

mysqli_close($baza);
echo("sukces!! <br>")
?>