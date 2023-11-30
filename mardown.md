Documentation sur l'utilisation des Markdowns
Les Markdowns sont un langage de balisage léger qui permet de formater du texte de manière simple et lisible. Voici quelques balises couramment utilisées :

Titres
Utilisez un dièse suivi d'un espace pour les niveaux de titres :

markdown
Copy code
# Titre de niveau 1
## Titre de niveau 2
### Titre de niveau 3
#### Titre de niveau 4
Listes
Créez des listes non ordonnées en utilisant un tiret suivi d'un espace ou un astérisque suivi d'un espace :

markdown
Copy code
- Élément 1
- Élément 2
    * Élément 2.1
    * Élément 2.2
Textes en gras et italique
Encadrez le texte par deux astérisques ** pour le gras et par des underscores _ pour l'italique.

markdown
Copy code
**Texte en gras**

_Texte en italique_
Liens
Pour insérer un lien, utilisez [Texte à afficher](lien URL) :

markdown
Copy code
[Google](https://google.net)
Blocs de code
Encadrez le code par des backticks ` pour un texte en ligne et par trois backticks pour un bloc de code :

markdown
Copy code
Utilisez la commande `ls -l` pour lister les fichiers.

for i in range(5):
print(i)