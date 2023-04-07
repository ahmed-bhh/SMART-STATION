//# pragma une fois

//# include  <tableau>
# include  <cstdint>
# include  <stdexcept>
# include  <string>
# include  <vector>
#include<array>


namespace qrcodegen {

/*
 * Un segment de données de caractères/binaires/de contrôle dans un symbole de code QR.
 * Les instances de cette classe sont immuables.
 * Le moyen de niveau intermédiaire pour créer un segment est de prendre les données de charge utile
 * et appelez une fonction d'usine statique telle que QrSegment::makeNumeric().
 * La façon de bas niveau de créer un segment est de personnaliser le tampon de bits
 * et appelez le constructeur QrSegment() avec les valeurs appropriées.
 * Cette classe de segment n'impose aucune restriction de longueur, mais les codes QR ont des restrictions.
 * Même dans les conditions les plus favorables, un QR Code ne peut contenir que 7089 caractères de données.
 * Tout segment plus long que cela n'a pas de sens dans le but de générer des codes QR.
 */
class  QrSegment  final {

    /* ---- Énumération des aides publiques ---- */

    /*
     * Décrit comment les bits de données d'un segment sont interprétés. Immuable.
     */
    public :  class  Mode  final {

        /* -- Constantes -- */

        public :  static  const Mode NUMERIC ;
        public :  static  const Mode ALPHANUMERIC ;
        public :  static  const Mode BYTE ;
        public :  static  const Mode KANJI ;
        public :  static  const Mode ECI ;


        /* -- Champs -- */

        // Les bits indicateurs de mode, qui sont une valeur uint4 (plage de 0 à 15).
        private :  int modeBits ;

        // Nombre de bits de comptage de caractères pour trois plages de versions différentes.
        private :  int numBitsCharCount[ 3 ] ;


        /* -- Constructeur -- */

        private : Mode( int mode, int cc0, int cc1, int cc2) ;


        /* -- Méthodes -- */

        /*
         * (Package-private) Renvoie les bits d'indicateur de mode, qui sont une valeur de 4 bits non signée (plage de 0 à 15).
         */
        public :  int  getModeBits () const ;

        /*
         * (Package-private) Renvoie la largeur en bits du champ de nombre de caractères pour un segment dans
         * ce mode dans un QR Code au numéro de version donné. Le résultat est dans la plage [0, 16].
         */
        public :  int  numCharCountBits ( int ver) const ;

    } ;



    /* ---- Fonctions d'usine statiques (niveau intermédiaire) ---- */

    /*
     * Renvoie un segment représentant les données binaires données encodées dans
     * mode octet. Tous les vecteurs d'octets d'entrée sont acceptables. Toute chaîne de texte
     * peut être converti en octets UTF-8 et encodé en tant que segment de mode octet.
     */
    public :  static QrSegment makeBytes ( const std::vector<std :: uint8_t > &data);


    /*
     * Renvoie un segment représentant la chaîne donnée de chiffres décimaux codés en mode numérique.
     */
    public :  static QrSegment makeNumeric ( const  char *chiffres);


    /*
     * Renvoie un segment représentant la chaîne de texte donnée encodée en mode alphanumérique.
     * Les caractères autorisés sont : 0 à 9, A à Z (uniquement en majuscule), espace,
     * dollar, pourcentage, astérisque, plus, tiret, point, barre oblique, deux-points.
     */
    public :  static QrSegment makeAlphanumeric ( const  char *text);


    /*
     * Renvoie une liste de zéro ou plusieurs segments pour représenter la chaîne de texte donnée. Le résultat
     * peut utiliser divers modes de segment et modes de commutation pour optimiser la longueur du flux binaire.
     */
    public:  static std::vector<QrSegment> makeSegments ( const  char *text);


    /*
     * Renvoie un segment représentant une interprétation de canal étendue
     * Désignateur (ECI) avec la valeur d'affectation donnée.
     */
    public :  static QrSegment makeEci ( long assignVal) ;


    /* ---- Fonctions d'assistance statiques publiques ---- */

    /*
     * Teste si la chaîne donnée peut être encodée comme un segment en mode alphanumérique.
     * Une chaîne est encodable si chaque caractère est dans l'ensemble suivant : 0 à 9, A à Z
     * (majuscules uniquement), espace, dollar, pourcentage, astérisque, plus, tiret, point, barre oblique, deux-points.
     */
    public:  static  bool  isAlphanumeric ( const  char *text);


    /*
     * Teste si la chaîne donnée peut être encodée comme un segment en mode numérique.
     * Une chaîne est encodable si chaque caractère est compris entre 0 et 9.
     */
    public:  static  bool  isNumeric ( const  char *text);



    /* ---- Champs d'instance ---- */

    /* L'indicateur de mode de ce segment. Accessible via getMode(). */
    private :Mode mode ;

    /* La longueur des données non codées de ce segment. Mesuré en caractères pour
     * mode numérique/alphanumérique/kanji, octets pour le mode octet et 0 pour le mode ECI.
     * Toujours zéro ou positif. Pas la même que la longueur en bits des données.
     * Accessible via getNumChars(). */
    private :  int numChars ;

    /* Les bits de données de ce segment. Accessible via getData(). */
    private : std :: vector < bool > data ;


    /* ---- Constructeurs (bas niveau) ---- */

    /*
     * Crée un nouveau segment de code QR avec les attributs et les données donnés.
     * Le nombre de caractères (numCh) doit être en accord avec le mode et la longueur du tampon de bits,
     * mais la contrainte n'est pas vérifiée. Le tampon de bits donné est copié et stocké.
     */
    public : QrSegment(Mode md, int numCh, const std::vector< bool > &dt);


    /*
     * Crée un nouveau segment de code QR avec les paramètres et les données donnés.
     * Le nombre de caractères (numCh) doit être en accord avec le mode et la longueur du tampon de bits,
     * mais la contrainte n'est pas vérifiée. Le tampon de bits donné est déplacé et stocké.
     */
    public : QrSegment(Mode md, int numCh, std::vector< bool > &&dt);


    /* ---- Méthodes ---- */

    /*
     * Renvoie le champ mode de ce segment.
     */
    public : Mode getMode () const ;


    /*
     * Renvoie le champ de nombre de caractères de ce segment.
     */
    public :  int  getNumChars () const ;


    /*
     * Renvoie les bits de données de ce segment.
     */
    public:  const std::vector< bool > & getData () const ;


    // (Package-private) Calcule le nombre de bits nécessaires pour encoder les segments donnés à
    // la version donnée. Renvoie un nombre non négatif en cas de succès. Sinon renvoie -1 si un
    // le segment a trop de caractères pour tenir dans son champ de longueur, ou le nombre total de bits dépasse INT_MAX.
    public:  static  int  getTotalBits ( const std::vector<QrSegment> &segs, int version);


    /* ---- Constante privée ---- */

    /* L'ensemble de tous les caractères légaux en mode alphanumérique, où
     * chaque valeur de caractère correspond à l'index dans la chaîne. */
    private :  char static  const  *ALPHANUMERIC_CHARSET;

} ;



/*
 * Un symbole QR Code, qui est un type de code-barres à deux dimensions.
 * Inventé par Denso Wave et décrit dans la norme ISO/IEC 18004.
 * Les instances de cette classe représentent une grille carrée immuable de cellules noires et blanches.
 * La classe fournit des fonctions d'usine statiques pour créer un code QR à partir de texte ou de données binaires.
 * La classe couvre la spécification QR Code Model 2, prenant en charge toutes les versions (tailles)
 * de 1 à 40, les 4 niveaux de correction d'erreurs et 4 modes d'encodage de caractères.
 *
 * Façons de créer un objet QR Code :
 * - Niveau élevé : prenez les données de la charge utile et appelez QrCode::encodeText() ou QrCode::encodeBinary().
 * - Niveau intermédiaire : Personnalisez la liste des segments et appelez QrCode::encodeSegments().
 * - Niveau bas : Personnalisez le tableau d'octets de mots de code de données (y compris
 * en-têtes de segment et remplissage final, hors mots de code de correction d'erreur),
 * fournissez le numéro de version approprié et appelez le constructeur QrCode().
 * (Notez que toutes les méthodes nécessitent de fournir le niveau de correction d'erreur souhaité.)
 */
class  QrCode  final {

    /* ---- Énumération des aides publiques ---- */

    /*
     * Le niveau de correction d'erreur dans un symbole QR Code.
     */
    public :  enum  class  Ecc {
        LOW = 0 ,   // Le QR Code peut tolérer environ 7% de mots de code erronés
        MEDIUM ,   // Le QR Code peut tolérer environ 15% de mots de code erronés
        QUARTILE,   // Le QR Code peut tolérer environ 25% de mots de code erronés
        HIGH ,   // Le QR Code peut tolérer environ 30% de mots de code erronés
    } ;


    // Renvoie une valeur comprise entre 0 et 3 (entier 2 bits non signé).
    private :  static  int  getFormatBits (Ecc ecl) ;



    /* ---- Fonctions d'usine statiques (niveau haut) ---- */

    /*
     * Renvoie un code QR représentant la chaîne de texte Unicode donnée au niveau de correction d'erreur donné.
     * En tant que limite supérieure conservatrice, cette fonction est garantie de réussir pour les chaînes qui ont 2953 ou moins
     * Unités de code UTF-8 (pas les points de code Unicode) si le niveau de correction d'erreur faible est utilisé. Le plus petit possible
     * La version QR Code est automatiquement choisie pour la sortie. Le niveau ECC du résultat peut être supérieur à
     * l'argument ecl si cela peut être fait sans augmenter la version.
     */
    public :  static QrCode encodeText ( const  char *text, Ecc ecl);


    /*
     * Renvoie un code QR représentant les données binaires données au niveau de correction d'erreur donné.
     * Cette fonction encode toujours en utilisant le mode segment binaire, pas n'importe quel mode texte. Le nombre maximal de
     * octets autorisés est de 2953. La plus petite version de code QR possible est automatiquement choisie pour la sortie.
     * Le niveau ECC du résultat peut être supérieur à l'argument ecl si cela peut être fait sans augmenter la version.
     */
    public:  static QrCode encodeBinary ( const std::vector<std:: uint8_t > &data, Ecc ecl);


    /* ---- Fonctions d'usine statiques (niveau intermédiaire) ---- */

    /*
     * Renvoie un code QR représentant les segments donnés avec les paramètres d'encodage donnés.
     * La plus petite version de code QR possible dans la plage donnée est automatiquement
     * choisi pour la sortie. Si boostEcl est vrai, alors le niveau ECC du résultat
     * peut être supérieur à l'argument ecl si cela peut être fait sans augmenter le
     * version. Le numéro de masque est soit compris entre 0 et 7 (inclus) pour forcer que
     * masque, ou -1 pour choisir automatiquement un masque approprié (ce qui peut être lent).
     * Cette fonction permet à l'utilisateur de créer une séquence personnalisée de segments qui bascule
     * entre les modes (tels que alphanumérique et octet) pour encoder le texte dans moins d'espace.
     * Il s'agit d'une API de niveau intermédiaire ; l'API de haut niveau est encodeText() et encodeBinary().
     */
    public:  static QrCode encodeSegments ( const std::vector<QrSegment> &segs, Ecc ecl,
        int minVersion= 1 , int maxVersion= 40 , int mask=- 1 , bool boostEcl= true );  // Tous les paramètres optionnels



    /* ---- Champs d'instance ---- */

    // Paramètres scalaires immuables :

    /* Le numéro de version de ce QR Code, qui est compris entre 1 et 40 (inclus).
     * Ceci détermine la taille de ce code-barres. */
    private :  int version ;

    /* La largeur et la hauteur de ce QR Code, mesurées en modules, entre
     * 21 et 177 (inclus). Ceci est égal à la version * 4 + 17. */
    private :  int size ;

    /* Le niveau de correction d'erreur utilisé dans ce QR Code. */
    private : Ecc errorCorrectionLevel ;

    /* L'indice du motif de masque utilisé dans ce QR Code, qui est compris entre 0 et 7 (inclus).
     * Même si un QR Code est créé avec masquage automatique demandé (masque = -1),
     * l'objet résultant a toujours une valeur de masque comprise entre 0 et 7. */
    private :  int mask ;

    // Grilles privées de modules/pixels, avec des dimensions de size*size :

    // Les modules de ce QR Code (false = blanc, vrai = noir).
    // Immuable après la fin du constructeur. Accessible via getModule().
    private: std::vector<std::vector< bool > > modules;

    // Indique les modules fonction qui ne sont pas soumis au masquage. Rejeté lorsque le constructeur a terminé.
    private : std::vector<std::vector< bool > > isFunction;



    /* ---- Constructeur (bas niveau) ---- */

    /*
     * Crée un nouveau QR Code avec le numéro de version donné,
     * niveau de correction d'erreur, octets de mot de code de données et numéro de masque.
     * Il s'agit d'une API de bas niveau que la plupart des utilisateurs ne devraient pas utiliser directement.
     * Une API de niveau intermédiaire est la fonction encodeSegments().
     */
    public: QrCode( int ver, Ecc ecl, const std::vector<std:: uint8_t > &dataCodewords, int msk);



    /* ---- Méthodes d'instances publiques ---- */

    /*
     * Renvoie la version de ce QR Code, dans la plage [1, 40].
     */
    public :  int  getVersion () const ;


    /*
     * Renvoie la taille de ce QR Code, dans la plage [21, 177].
     */
    public :  int  getSize () const ;


    /*
     * Renvoie le niveau de correction d'erreur de ce QR Code.
     */
    public: Ecc getErrorCorrectionLevel () const ;


    /*
     * Renvoie le masque de ce QR Code, dans la plage [0, 7].
     */
    public :  int  getMask () const ;


    /*
     * Renvoie la couleur du module (pixel) aux coordonnées données, ce qui est faux
     * pour le blanc ou vrai pour le noir. Le coin supérieur gauche a les coordonnées (x=0, y=0).
     * Si les coordonnées données sont hors limites, alors false (blanc) est renvoyé.
     */
    public :  bool  getModule ( int x, int y) const ;


    /*
     * Renvoie une chaîne de code SVG pour une image représentant ce QR Code, avec le numéro donné
     * de modules frontières. La chaîne utilise toujours des retours à la ligne Unix (\n), quelle que soit la plate-forme.
     */
    public: std::string toSvgString ( int border) const ;



    /* ---- Méthodes d'assistance privées pour le constructeur : modules de fonction de dessin ---- */

    // Lit le champ de version de cet objet, et dessine et marque tous les modules fonction.
    private :  void  drawFunctionPatterns ();


    // Dessine deux copies des bits de format (avec son propre code de correction d'erreur)
    // basé sur le masque donné et le champ de niveau de correction d'erreur de cet objet.
    private :  void  drawFormatBits ( int msk );


    // Dessine deux copies des bits de version (avec son propre code de correction d'erreur),
    // basé sur le champ de version de cet objet, ssi 7 <= version <= 40.
    private :  void  drawVersion ();


    // Dessine un motif de recherche 9*9 incluant le séparateur de bordure,
    // avec le module central en (x, y). Les modules peuvent être hors limites.
    private:  void  drawFinderPattern ( int x, int y);


    // Dessine un motif d'alignement 5*5, avec le module central
    // à (x, y). Tous les modules doivent être dans les limites.
    private:  void  drawAlignmentPattern ( int x, int y);


    // Définit la couleur d'un module et le marque comme module fonction.
    // Uniquement utilisé par le constructeur. Les coordonnées doivent être dans les limites.
    private:  void  setFunctionModule ( int x, int y, bool isBlack);


    // Renvoie la couleur du module aux coordonnées données, qui doivent être comprises dans la plage.
    private :  bool  module ( int x, int y) const ;


    /* ---- Méthodes d'assistance privées pour le constructeur : mots de code et masquage ---- */

    // Renvoie une nouvelle chaîne d'octets représentant les données données avec la correction d'erreur appropriée
    // mots de code qui lui sont ajoutés, en fonction de la version de cet objet et du niveau de correction d'erreurs.
    private: std::vector<std :: uint8_t > addEccAndInterleave ( const std::vector<std :: uint8_t > &data) const ;


    // Dessine la séquence donnée de mots de code 8 bits (données et correction d'erreurs) sur l'ensemble
    // zone de données de ce QR Code. Les modules de fonction doivent être marqués avant d'être appelés.
    private:  void  drawCodewords ( const std::vector<std:: uint8_t > &data);


    // XORs les modules de mots de code dans ce code QR avec le modèle de masque donné.
    // Les modules fonction doivent être marqués et les bits du mot de code doivent être dessinés
    // avant le masquage. En raison de l'arithmétique de XOR, l'appel de applyMask() avec
    // la même valeur de masque une seconde fois annulera le masque. Une finale bien formée
    // Le code QR nécessite exactement un masque (pas zéro, deux, etc.) appliqué.
    private:  void  applyMask ( int msk);


    // Calcule et renvoie le score de pénalité en fonction de l'état des modules actuels de ce code QR.
    // Ceci est utilisé par l'algorithme de choix de masque automatique pour trouver le modèle de masque qui donne le score le plus bas.
    private :  long  getPenaltyScore () const ;



    /* ---- Fonctions d'assistance privées ---- */

    // Renvoie une liste ascendante des positions des motifs d'alignement pour ce numéro de version.
    // Chaque position est dans la plage [0,177) et est utilisée à la fois sur les axes x et y.
    // Cela pourrait être implémenté en tant que table de recherche de 40 listes de longueur variable d'octets non signés.
    private: std::vector< int > getAlignmentPatternPositions () const ;


    // Renvoie le nombre de bits de données qui peuvent être stockés dans un QR Code du numéro de version donné, après
    // tous les modules fonction sont exclus. Cela inclut les bits restants, il peut donc ne pas être un multiple de 8.
    // Le résultat est dans la plage [208, 29648]. Cela pourrait être implémenté sous la forme d'une table de recherche à 40 entrées.
    private :  static  int  getNumRawDataModules ( int ver) ;


    // Renvoie le nombre de mots de code de données 8 bits (c'est-à-dire sans correction d'erreur) contenus dans n'importe quel
    // Code QR du numéro de version et du niveau de correction d'erreur donnés, avec les bits restants supprimés.
    // Cette fonction pure sans état pourrait être implémentée sous la forme d'une table de recherche (40*4) cellules.
    private :  static  int  getNumDataCodewords ( int ver, Ecc ecl) ;


    // Renvoie un polynôme générateur de Reed-Solomon ECC pour le degré donné. Cela pourrait être
    // implémenté comme une table de recherche sur toutes les valeurs de paramètres possibles, au lieu d'un algorithme.
    private:  static std::vector<std:: uint8_t > reedSolomonComputeDivisor ( int degree);


    // Renvoie le mot de code de correction d'erreur Reed-Solomon pour les données données et les polynômes diviseurs.
    private:  static std::vector<std :: uint8_t > reedSolomonComputeRemainder ( const std::vector<std :: uint8_t > &data, const std::vector<std :: uint8_t > &divisor);


    // Renvoie le produit des deux éléments de champ donnés modulo GF(2^8/0x11D).
    // Toutes les entrées sont valides. Cela pourrait être implémenté sous la forme d'une table de recherche 256*256.
    private :  static std :: uint8_t  reedSolomonMultiply (std :: uint8_t x, std :: uint8_t y);


    // Ne peut être appelé qu'immédiatement après l'ajout d'un run blanc, et
    // renvoie 0, 1 ou 2. Une fonction d'assistance pour getPenaltyScore().
    private:  int  finderPenaltyCountPatterns ( const std::array< int , 7 > &runHistory) const ;


    // Doit être appelé à la fin d'une ligne (ligne ou colonne) de modules. Une fonction d'assistance pour getPenaltyScore().
    private:  int  finderPenaltyTerminateAndCount ( bool currentRunColor, int currentRunLength, std::array< int , 7 > &runHistory) const ;


    // Pousse la valeur donnée au premier plan et supprime la dernière valeur. Une fonction d'assistance pour getPenaltyScore().
    private:  void  finderPenaltyAddHistory ( int currentRunLength, std::array< int , 7 > &runHistory) const ;


    // Renvoie vrai si et seulement si le ième bit de x est mis à 1.
    private:  static  bool  getBit ( long x, int i);


    /* ---- Constantes et tables ---- */

    // Le numéro de version minimum pris en charge dans la norme QR Code Model 2.
    public :  static  constexpr  int MIN_VERSION =   1 ;

    // Le numéro de version maximum pris en charge dans la norme QR Code Model 2.
    public :  static  constexpr  int MAX_VERSION = 40 ;


    // À utiliser dans getPenaltyScore(), lors de l'évaluation du meilleur masque.
    private :  static  const  int PENALTY_N1 ;
    private :  static  const  int PENALTY_N2 ;
    private :  static  const  int PENALTY_N3 ;
    private :  static  const  int PENALTY_N4 ;


    private :  static  const std :: int8_t ECC_CODEWORDS_PER_BLOCK[ 4 ][ 41 ];
    private :  static  const std :: int8_t NUM_ERROR_CORRECTION_BLOCKS[ 4 ][ 41 ];

} ;



/* ---- Classe d'exception publique ---- */

/*
* Lancé lorsque les données fournies ne correspondent à aucune version de code QR. Les moyens de gérer cette exception incluent :
 * - Diminuer le niveau de correction d'erreur s'il était supérieur à Ecc::LOW.
 * - Si la fonction encodeSegments() a été appelée avec un argument maxVersion, alors augmentez
* le s'il était inférieur à QrCode::MAX_VERSION. (Ce conseil ne s'applique pas aux autres
 * fonctions d'usine car elles recherchent toutes les versions jusqu'à QrCode::MAX_VERSION.)
 * - Divisez les données de texte en segments meilleurs ou optimaux afin de réduire le nombre de bits requis.
 * - Modifiez le texte ou les données binaires pour qu'ils soient plus courts.
 * - Modifiez le texte pour qu'il corresponde au jeu de caractères d'un mode de segment particulier (par exemple alphanumérique).
 * - Propager l'erreur vers le haut à l'appelant/utilisateur.
 */
class  data_too_long : public  std ::length_error {

    public :  explicit  data_too_long ( const std::string &msg);

} ;



/*
* Une séquence de bits pouvant être ajoutée (0s et 1s). Principalement utilisé par QrSegment.
 */
class  BitBuffer  final : public std::vector< bool > {

    /* ---- Constructeur ---- */

    // Crée un tampon de bits vide (longueur 0).
    public : BitBuffer();



    /* ---- Méthode ---- */

    // Ajoute le nombre donné de bits de poids faible de la valeur donnée
    // à ce tampon. Requiert 0 <= len <= 31 et val < 2^len.
    public :  void  appendBits (std :: uint32_t val, int len);

} ;

}
