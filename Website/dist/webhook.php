<?php
include "data.php";
error_reporting(1);
$webHS = json_decode(file_get_contents('php://input'), true);
$topic = $webHS['topic'];
$payload = $webHS['payload'];

if ($topic == 'dicky/bed/suhu') {
   $sql = "INSERT INTO suhu (ruangan,suhu) VALUES ('Bedroom','$payload')";
}
if ($topic == 'dicky/living/suhu') {
   $sql = "INSERT INTO suhu (ruangan,suhu) VALUES ('Living Room','$payload')";
}
if ($topic == 'dicky/kitchen/suhu') {
   $sql = "INSERT INTO suhu (ruangan,suhu) VALUES ('Kitchen','$payload')";
}
if ($topic == 'dicky/bath/suhu') {
   $sql = "INSERT INTO suhu (ruangan,suhu) VALUES ('Bath','$payload')";
}

if ($topic == 'dicky/bed/kelembapan') {
   $sql = "INSERT INTO kelembapan (ruangan,kelembapan) VALUES ('Bedroom','$payload')";
}
if ($topic == 'dicky/living/kelembapan') {
   $sql = "INSERT INTO kelembapan (ruangan,kelembapan) VALUES ('Living Room','$payload')";
}
if ($topic == 'dicky/kitchen/kelembapan') {
   $sql = "INSERT INTO kelembapan (ruangan,kelembapan) VALUES ('Kitchen','$payload')";
}
if ($topic == 'dicky/bath/kelembapan') {
   $sql = "INSERT INTO kelembapan (ruangan,kelembapan) VALUES ('Bath','$payload')";
}

if ($topic != null) {
   mysqli_query($conn, $sql);

}
?>