-- First, find the id of 'Kevin' in 'people' table
-- Then, from 'stars' table find the list of movie_id starred by Kevin.
-- After that, we 'name' of person who also starred in those list of movie_id.
SELECT name FROM people
JOIN stars ON people.id = stars.person_id
WHERE movie_id IN (SELECT movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = "Kevin Bacon" AND birth = 1958)) AND name != "Kevin Bacon";