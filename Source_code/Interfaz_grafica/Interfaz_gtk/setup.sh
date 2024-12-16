#!/bin/bash
# Create all the required directories
Install_directory="$HOME/.pccae32/"
ListOf_directories=("Firmware/Main_board" "Modules/pedals" "Modules/shifter" "Firmware_upload_tool" "GUI" "GUI/exec")

# adding a bit of color
BGreen='\033[1;32m'
NC='\033[0m' # No Color
echo -e "$BGreen Creating all the required directories $NC"

for dir in ${ListOf_directories[@]}; do
	mkdir -v -p $Install_directory$dir	
done

# Move all the required directories of the GUI
cp ../../Interfaz_grafica/Interfaz_gtk/build/executable $Install_directory${ListOf_directories[4]}/exec -r #path of executable file
cp ../../Interfaz_grafica/Interfaz_gtk/src_images $Install_directory${ListOf_directories[4]} -r
cp ../../Interfaz_grafica/Interfaz_gtk/gladeFiles $Install_directory${ListOf_directories[4]} -r 
cp ../../Desktop_files/start_GUI.sh $Install_directory${ListOf_directories[4]}/exec 

chmod +x $Install_directory/GUI/exec/executable
chmod +x $Install_directory/GUI/exec/start_GUI.sh
#

echo -e "$BGreen Creating shortcut $NC"

echo "[Desktop Entry]
Categories=Games
Comment[es_MX]=
Comment=
Comment[en_US]=Panel de configuración de volante
Exec='`echo $HOME`/.pccae32/GUI/exec/start_GUI.sh'
GenericName[es_MX]=Panel de Configuracion CAE32
GenericName=Panel de Configuracion CAE32
Icon=`echo $HOME`/.pccae32/GUI/src_images/logo.png
MimeType=
Name[es_MX]=PCCAE32
Name=PCCAE32
Name[en_US]=PCCAE32
Path=
StartupNotify=true
Terminal=false
TerminalOptions=
Type=Application
X-DBUS-ServiceName=
X-DBUS-StartupType=
X-KDE-SubstituteUID=false
X-KDE-Username=">`echo $HOME`/.local/share/applications/pccae32.desktop
chmod +x `echo $HOME`/.local/share/applications/pccae32.desktop
# adding 
