<!DOCTYPE html> <html>
	<head>
		<meta charset="utf-8" />
		<link rel="stylesheet" href="style.css" />
		<title>Infos carte Y</title>
		<script type="text/javascript" src="jquery.js"></script>
			<script type="text/javascript">
			
			
				// WebSocket ReadyState Constants
				CONNECTING = 0;
				OPEN       = 1;
				CLOSING    = 2;
				CLOSED     = 3;
				
				
				ws = new WebSocket('ws://192.168.0.2:8080/');
				
							
				var auto_refresh = setInterval(
					function(){	ws.send("DATA_RQST");// else send a data request					
								}, 200);
	

				//Message Received
				ws.onmessage = function(ev) {
					$('#sensor_list').load('content.php',{json_str:ev.data}).fadeIn("slow");
				};
					
				//Send a Message
				$('#send').click(function(){
					var mymessage = 'This is a test message';
					ws.send(mymessage);
				});
						
						
				//Error
				ws.onerror = function(ev) {
					write_label("sensor_list", "Pas de données disponible pour le moment");
					//alert('Error '+ev.data);					
				};
					   
				
				//Connection close
				ws.onclose = function(ev) {
					write_label(document.getElementById('sensor_list'), 'Pas de données disponible pour le moment');
					alert('Disconnected ! please refresh (F5)');
				}
				
				function write_label(label,txt)
				{
					label.innerHTML= txt;
				}
				
				
		</script>

	</head>
	<body>

		<h1> Capteurs communiquant avec le Rasberry 3B</h1>
		<p> <a href="index.php">Retour à l'acceuil</a></p>
		

			<div id="sensor_list">
				<!-- This part of code is refreshed every second to print the capteur's informations -->
			</div>

			</div>
		</div>		
	</body>

	<footer id="footer">
	    <!-- Contenu du pied de page -->
		Projet Electronique de Florian Le Bourhis, Norbert Parker-Soues, Richard Taupiac  <br />

	</footer>

</html> 
