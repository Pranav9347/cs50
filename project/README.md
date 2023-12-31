# RagaIdentify
#### Video Demo:  <URL HERE>https://youtu.be/SOVg-OwbLyo

## About the project
###   This is a web application that enables users to find:

   - the ragam (scale) of a classical song (Carnatic style)

   - all the classical songs which are set in the given ragam

### UX
- Users can create an account with their username and password.

- All the 'ragam' searches can be viewed in the 'search history' section under the 'Account' dropdown menu.

- Users can also change their username, password and can delete their account

![RagaIdentify homepage](homepg.png "a title")


### How to use
#### Find ragam
- Select the notes which appear in the raga-scale by checking the buttons for Pa or choosing the options for Re, Ga, Ma, Da and Ni notes
and click on the submit button to find the ragam.

- Click on reset if you want to clear your choices.


![RagaIdentify songs](songs.png "a title")
#### Find songs
- Type the name of the raga in the search bar.

- On clicking 'search', a list of some of the Carnatic classical style songs appears which are set in that ragam.



### What is a ragam?
Every piece of music arises from a unique combination of any of the 12 notes, which in Western music is represented as C,  C sharp(D flat),  D,  D sharp(E flat),  E,  F,  F sharp(G flat),  G,  G sharp(A flat),  A,  A sharp(B flat),  and B , and in Carnatic(Indian) Music represented as Sa , Re1 , Re2 (Ga1), Ga2 (Re3), Ga3 , Ma1 , Ma2 , Pa ,  Da1 ,  D2,  Ni2 (Da3), and  Ni3.

Every Indian classical style song has a unique characteristic called the 'ragam'. A 'ragam' is the name given to a set of musical notes appearing in a particular pattern which entirely make up the song. Hence raga decides the tune/melody of the song.

Ragas also decide the mood of the song: for example- Hamsadhwani and DhiraSankarabharanam impart happy mood to the song,  Atana for angry mood,  Shivaranjani and Vasantha Bhairavi can make you cry!

Note that in Carnatic Classical songs any of the above 7 notes can appear (with few exceptions). And thus a ragam has 7 notes in its scale.

The concept of ragam is not limited to just the set of distinct notes appearing in a song but also the unique patterns in which they appear. Hence there are 2 scales for a ragam: the ascending scale(Aarohanam) and the descending scale (Avarohanam). These are the patterns in which the notes appear in the song.

#### Classification of Carnatic Ragas
There are 2 main types of ragas:
- Janaka ragas - parent ragas

- Janya ragas - derived ragas

##### [Janaka ragam](https://en.wikipedia.org/wiki/Melakarta): (Also known as Melakarta ragam) is a complete ragam, i.e contains all the 7 notes (Sa, Re, Ga, Ma, Pa, Da, Ni) in both the ascending and descending scales.
There are 72 Melakarta ragas in Carnatic Music, each of which has a number of Janya ragas derived from it.

##### [Janya ragam](https://en.wikipedia.org/wiki/List_of_Janya_ragas):  is an incomplete ragam containing a subset of the 7 notes (Sa, Re, Ga, Ma, Pa, Da, Ni) in either the ascending or the descending scales. The notes appearing in the scale of a Janya ragam is derived from its parent/Janaka ragam.
There are more than a thousand janya ragas, but only a few hundred are popular and sung today.

There are again subdivisions under the Janya ragas like 'Upanga ragas' (the notes are purely derived from their parent ragas) and 'Bhashanga ragas' (few external notes other than the ones in their parent ragas appear).



### Working of the project
- This application is supported by a database which consists of all of the 72 *Janaka ragas* and some of the popular *Janya ragas*. When the user submits the list of distinct notes, that list is matched with the notes of ragas in the database and the matching ragam is returned.

#### Design of 'find ragam'
As every ragam must have 'Sa' the base note, 'Sa' option is seleted by default. As there can be different types of 'Re',
'Ga', 'Ma', 'Da' and 'Ni', you can choose the required note from the dropdown. As for 'Pa', since it has no variation, there is an option to either include (check) or exclude (uncheck) 'Pa' option


- Few popular Carnatic style songs (which are learnt formally by a music student) are also included in the database. Upon searching for songs of a given ragam, all the matching songs which are set in that ragam are returned.

### Overall design
- The login page asks the user for his username and password and enables access to the app if the credentials are valid. The user can register first if he/she does not have an account. The username has to be unique (different from the ones already existing) The password has to be atleast 8 characters in length with atleast 1 special character.
- If the user enters wrong password, appropriate error message is displayed
- After successful registration, a success message is displayed
- After successful login the user is lead to the homepage where the user can use the 'find ragam'. Links to 'find songs', 'search history', 'change username', 'change password' and 'delete account' are provided under the respective headings in the sidebar.
- In the 'find ragam' page, the user can choose the required notes and get the ragam. If it is a parent raga, it is indicated along with its 'Melakarta number'; if it is a derived ragam, it is displayed. 'Could not find ragam' message is displayed
- In the 'find songs' page, the user can type the ragam name and get the songs set in that ragam. The ragam name has to be correctly spelled as in [list of ragas](https://en.wikipedia.org/wiki/List_of_Janya_ragas)
- Help section in the top bar helps users use the app
- Account section
  - While changing the password or deleting account, if old password is given incorrectly, appropriate error message is displayed.
  - Search history lists all the raga searches done from the first search



### Limitations
Note that while finding ragam, only the ascending scale is considered, which could uniquely identify the 72 *Janaka ragas*. *Janya ragas* are complex and can have complicated patterns in their scale which is difficult to store and match. But in case of few *Janya ragas* having simple ascending scale, results can be obtained.




### References
- Database source: [Wikipedia](https://en.wikipedia.org/wiki/List_of_Janya_ragas)
- Image source: [ShutterStock](https://www.shutterstock.com/image-vector/vector-illustration-abstract-music-collage-background-620624174)
- Inspiration from CS50 Finance
