	echo "-- Make file starting -- \n"
presentDir=.
templist=temp.txt
SYSTEMC_HOME=/usr/local/systemc230/

if ls *.cpp|sed 's/\.cpp//g'> $presentDir/$templist
then
    echo "[$(date)]::File $templist for cpp created successfully\n"
else
    echo "[$(date)]::ERROR:File $templist for cpp was not created\n"
fi

for i in `cat $templist`
do
echo "[$(date)]::$i.cpp is being exectuted\n" 
   if  g++ -I $SYSTEMC_HOME/include -L $SYSTEMC_HOME/lib-linux -Wl,-rpath=$SYSTEMC_HOME/lib-linux -o $i.o $i.cpp -lsystemc -lm
   then
     echo "[$(date)]::$i.o created successfully\n"
   else
     echo "[$(date)]::File $i.o was not created\n"
   fi
done

if rm $templist
  then
    echo "[$(date)]::$templist for cpp was deleted successfully\n"
  else
    echo "[$(date)]::ERROR:'$templist' for cpp was not deleted\n"
fi

if ls *.o|sed 's/\.o//g'> $presentDir/$templist
then
    echo "[$(date)]::File $templist for out created successfully\n"
else
    echo "[$(date)]::ERROR:File $templist for out was not created\n"
fi

for i in `cat $templist`
do
	if ./$i.o >> a.txt
	then
		 echo "[$(date)]::$i.o executed successfully\n"
	else
		echo "[$(date)]::File $i.o was not executed\n"
   fi

done

for i in `cat $templist`
do
        if rm ./$i.o
        then
                 echo "[$(date)]::$i.o deleted  successfully\n"
        else
                echo "[$(date)]::File $i.o was not deleted \n"
   fi

done

if rm $templist
  then
    echo "[$(date)]::$templist for out was deleted successfully\n"
  else
    echo "[$(date)]::ERROR:'$templist' for out was not deleted\n"
fi
	echo "Process ends ----\n"

