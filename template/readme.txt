Default:
--------
Die Seite wird aus den Templates header, start und footer
zusammengesetzt. Ajax Calls haben keinen header und footer.


Kapitel:
--------
Wenn ein Kapitel anders dargestellt werden soll, braucht
es ein eigenes Template unter chapters/
Das File muss [Kapitelname].phtml heissen
Existiert kein Template für ein Kapitel,
wird per Default das Template Default.phtml geladen.

Error:
------
Wird eine Exception geworfen in der view class, wird das Template
sys/404.phtml geladen und mit dem Exception-Text ausgegeben.