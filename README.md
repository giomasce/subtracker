# README (in Italian) #

## Istruzioni per utilizzare il Subtracker ##

* Compilare OpenCV, Boost e `subtracker/cpp/subtracker2014.cpp` (glisseremo su questi punti).
* Collegare la webcam giusta via USB.
* Utilizzare il programma `streaming/v4l2_source.c` per interfacciarsi con la webcam e scrivere frame in formato JPEG su standard output.
Opzioni utili sono: `-d DEVICE` (per indicare la webcam), `-a` (si riavvia automaticamente ad ogni crash, per esempio se la webcam viene scollegata e ricollegata), `-f` (forza la risoluzione 640x480 e formato MPEG).
* Mandare i frame in pipe a `streaming/monitor_tee.py`, il quale ascolta (e manda i frame) su una porta TCP (default 2204) e opzionalmente fa il dump sull'hard disk per l'archiviazione (serve tanta memoria, ordine dei 500 GB).
L'archiviazione dei frame su disco è attivata/disattivata premendo il tasto `r` (crea un file da 1 GB ogni 3 minuti circa).
Riassumendo, un comando ragionevole è `./v4l2_source -d /dev/video0 -a -f | ./monitor_tee.py 640 480`.
Opzioni utili di `monitor_tee.py` sono: `-p PORT` (per indicare la porta), `-d DIRECTORY` (cartella per l'archiviazione).
* Di default, `subtracker2014` si connette a localhost sulla porta 2204.