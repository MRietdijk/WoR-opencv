# WoR Opencv opdracht

Om het project te compileren, voer het volgende commando uit in de terminal, in de projectmap:

`make`

Om een plaatje te gebruiken als 'source' voeg een plaatje toe in de projectmap, of maak een folder 'images' aan in het project om alles gescheiden te houden.

Hierna typ het volgende commando om het plaatje te gebruiken als source:

`./main file <padnaam van het plaatje relatief aan de projectmap>`

Als je gebruik wilt maken van de camera functie, typ dan het volgende commando:

`./main camera <camera die je wilt gebruiken>`

Het commando hierboven vraagt naar een camera die je wilt gebruiken. In mijn geval is dit:

`/dev/video1`

Dus mijn commando zou er als volgt hebben uitgezien:

`./main camera /dev/video1`