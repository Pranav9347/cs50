SELECT AVG(rating) FROM ratings WHERE movie_id IN (SELECT id FROM movies WHERE movies.year = 2012);
