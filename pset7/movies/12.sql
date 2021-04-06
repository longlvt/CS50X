-- First, find the Ids of the movies starred by Johnny Depp.
-- Then, from that list of Ids, find the 'title' of which also starred by Helena.
SELECT title FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE name = "Helena Bonham Carter"
AND movies.id IN (SELECT movies.id FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE name = "Johnny Depp");