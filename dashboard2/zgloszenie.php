<?php
    echo "Łączenie z bazą danych...";
    $baza_danych = mysqli_connect("localhost","root","","wedkowanie");
    if($baza_danych != FALSE){
        echo "sukces!<br>";
    }
    else{
        echo "blad!!!<br>";
    }

    $zapytanie = mysqli_query($baza_danych,"insert into zawody_wedkarskie values(NULL,0," . $_POST['lowisko'] . ",'" . $_POST['data'] . "',' " . $_POST['sedzia'] . "')");
    echo "wyslano zapytanie<br>";

    mysqli_close($baza_danych);
    echo "zamknieto połączenie z bazą danych<br>";
?>