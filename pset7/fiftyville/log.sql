-- Keep a log of any SQL queries you execute as you solve the mystery.


-- 1. Accessed crime scene reports for more details about the crime:
SELECT * FROM crime_scene_reports
WHERE year = 2021 AND month = 7 AND street = 'Humphrey Street' AND day = 28;

--2. Accessed interviews data for useful information:
SELECT * FROM interviews
WHERE year = 2021 AND month = 7 AND day = 28 AND INSTR(transcript, 'bakery') > 0;


--3. Based on the info provided by interviews(161, 162, 163), accessed bakery security logs, recorded atm_transactions, accessed phone calls, noted the Fiftyville airport's details, accessed flights, noted the required flights' passengers:(Finding the thief)
SELECT name FROM people
WHERE id IN (SELECT person_id FROM bank_accounts
WHERE account_number IN (SELECT account_number FROM atm_transactions
WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location='Leggett Street' AND transaction_type='withdraw')) INTERSECT
SELECT name FROM people
WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs
WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 and minute >= 15 and minute <= 25) INTERSECT
SELECT name FROM people
WHERE phone_number IN (SELECT caller FROM phone_calls
WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60) INTERSECT
SELECT name FROM people
WHERE passport_number IN (SELECT passport_number FROM passengers
WHERE flight_id IN (SELECT id FROM flights
WHERE origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville') AND year = 2021 AND month = 7 AND day = 29 ORDER BY hour LIMIT 1));

--This gives the thief: 'Bruce'

--4. Finding the thief's accomplice:
SELECT name FROM people
WHERE phone_number IN (SELECT receiver FROM phone_calls
WHERE caller = (SELECT phone_number FROM people WHERE name = 'Bruce') AND year = 2021 AND month = 7 AND day = 28 AND duration < 60);

-- Thus the thief's accomplice: 'Robin'


--5. City to which the thief escaped to: 'New York City'
1. SELECT city FROM airports WHERE id = (SELECT destination_airport_id FROM flights WHERE origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville') AND year = 2021 AND month = 7 AND day = 29 ORDER BY hour LIMIT 1);



