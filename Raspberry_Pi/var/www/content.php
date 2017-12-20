<?php

	//$date =getdate();
	//var_dump($date[0]);
	echo "<br />". "<br />";
	
		$string = $_POST['json_str'];
			
				$json = json_decode($string, true);
				$mesure=array();
				$unit=array();
				$id_carte=array();
				$id_capteur=array();
				$nb_capt_carte =array();
				$nb_capt_pass = 0 ;
			
				//if (count(json['cartes']!=0){
				foreach ($json['cartes'] as $key) {
					array_push($id_carte, $key['id']);
					array_push($nb_capt_carte, count($key['capteurs']));
						foreach ($key['capteurs'] as $key1) {
							array_push($id_capteur, $key1['id']);
							array_push($mesure, $key1['mesure']);
							array_push($unit, $key1['unit']);
							}
						}
					
					for ($j =0; $j< count($id_carte); $j++) {
						echo " carte numéro : ", $id_carte[$j] ."<br />". "<br />";
						for ($i =0; $i< $nb_capt_carte[$j]; $i++) {
							if ($unit[$nb_capt_pass]=="C  "){
								echo "température de la carte           ",  $id_carte[$j] ,   "        : ", $mesure[$nb_capt_pass] . " °C <br />". "<br />" ;
							} elseif ($unit[$nb_capt_pass]=="% 0"){
								echo "position du potard 0 de la carte  ",  $id_carte[$j]  ,  "        : ", $mesure[$nb_capt_pass] . " % <br />". "<br />" ;
							} elseif ($unit[$nb_capt_pass]=="% 1"){
								echo "position du potard 1 de la carte  ",  $id_carte[$j]  ,  "        : ", $mesure[$nb_capt_pass] . " % <br />". "<br />" ;
							} elseif ($unit[$nb_capt_pass]=="lux"){
								echo "luminosité de la carte            ",  $id_carte[$j]  ,  "        : ", $mesure[$nb_capt_pass] . " lux <br />". "<br />" ;
							} elseif ($nit[$nb_capt_pass]=="g_X"){
								echo "accéléromètre de la carte         ",  $id_carte[$j]  ,  "  axe X : ", $mesure[$nb_capt_pass] . " g <br />". "<br />" ;
							} elseif ($nit[$nb_capt_pass]=="g_Y"){
								echo "accéléromètre de la carte         ",  $id_carte[$j]  ,  "  axe Y : ", $mesure[$nb_capt_pass] . " g <br />". "<br />" ;
							} elseif ($nit[$nb_capt_pass]=="g_Z"){
								echo "accéléromètre de la carte         ",  $id_carte[$j]  ,  "  axe Z : ", $mesure[$nb_capt_pass] . " g <br />". "<br />" ;
							}
					
							echo "<br/>";
							$nb_capt_pass =$nb_capt_pass +1;
						}
					
						echo "--------------------------------------------------------------" . "<br/>";
					}
			

?>
