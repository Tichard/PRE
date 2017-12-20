<!DOCTYPE html>
<html>
	<head>
		<meta charset="utf-8" />
		<link rel="stylesheet" href="style.css" />
		<title>video du Raspberry Pi 3B</title>

	</head>
	<body>
		<h1> Contrôle de la caméra du Raspberry pi 3B</h1>
		<p> <a href="index.php">Retour à l'acceuil</a></p>
		
		<p id="counter">
		
		<div id="control">
				<p>
				<button onClick="start_vid()">Démarrer la vidéo </button>
				<button onClick="stop_vid()">Arrêter la vidéo </button> 
				</p>
				<p>
				<button onClick="show_vid()">Afficher la vidéo </button> 
				<button onClick="show_obj()">Afficher les objets </button> 
				<p>
		</div>
		
		
		<div id="client">
		
			<script type="text/javascript">
			
			// WebSocket ReadyState Constants
			CONNECTING = 0;
			OPEN       = 1;
			CLOSING    = 2;
			CLOSED     = 3;
					
			ws = new WebSocket('ws://192.168.0.2:8181/');
			
			var auto_refresh = setInterval(
			function(){	ws.send("COUNT");// else send a data request					
						}, 100);
		
	
			//Message Received
			ws.onmessage = function(ev) {
					document.getElementById("counter").innerHTML = ev.data;	
					}; 
					
	
			function start_vid()
			{
				ws.send("CAMERA_ON");
			}
			
			function stop_vid()
			{
				ws.send("CAMERA_OFF");
				ws.send("CAMERA_OFF");
			}
			function show_vid()
			{
				ws.send("VIDTHRU");
			}		
			function show_obj()
			{
				ws.send("VIDOBJ");
			}
			
			
			
			
			</script>
			
		</div>
		
	</body>

	<footer id="footer">
	    <!-- Contenu du pied de page -->	
		Projet Electronique de Florian Le Bourhis, Norbert Parker-Soues, Richard Taupiac  <br />

	</footer>
	
	

</html> 
