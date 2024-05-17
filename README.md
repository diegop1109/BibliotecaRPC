para lanzar el proyecto de prefencia usar una distribucion de linux debian, para este proyecto use Ubuntu 22.04 con las siguientes configuraciones:
En una terminal escribir los siguientes comandos:
1. instalar rpcbind y portmap: sudo apt-get install rpcbind portmap

2. en el caso se quiera generar un codigo desde cero a traves de la plantilla (fichero GestorBiblioteca.x): rpcgen -a calculadora.x. este comando genera los otros ficheros de la biblioteca

3. usar el comando: dpkg -l|grep rpc, y buscar los paquetes: libtirpc3, libtirpc-common, libtirpc-dev y rpcbind.

4. confirmar en el fichero MAkefile que se tengan las siguientes configuraciones:
         CFLAGS += -g -I/usr/include/tirpc
         LDLIBS += -lnsl -ltirpc

5. Para compilar y guardar los cambios realizados en el cliente y servidor se necesita el siguiente comando: make -f ./Makefile.GestorBiblioteca (siempre que se hagan cambios en cliente o servidor se debe correr este comando en una terminal dentro del fichero para guardar los cambios)

6. Para correr el servidor usar el comando: ./GestorBiblioteca_server

7. Para correr el cliente usar el comando: ./GestorBiblioteca_client localhost
