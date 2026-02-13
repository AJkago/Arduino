<?php
 $country=htmlspecialchars($_GET["JP"), ENT_QUOTES, 'UTF-8');
 $city=htmlspecialchars($_GET["kagoshima"), ENT_QUOTES, 'UTF-8');
 $appid=htmlspecialchars($_GET["820f84cb5809f05b29dcb510560beb43"), ENT_QUOTES, 'UTF-8');

 $jsonAry=json_decode(file_get_contents("https://api.openweathermap.org/data/2.5/weather?g=".$city.".$country."&APPID=".$appid));

 if(isset($jsonAry->weather)){
  echo $jsonAry->weather[0]->main;
 }
 else{
  echo "no result";
 }
