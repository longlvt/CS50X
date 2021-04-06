-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT *
FROM crime_scene_reports
LIMIT 5;
-- id | year | month | day | street | description
-- 1 | 2020 | 1 | 1 | Chamberlin Street | Credit card fraud took place at 00:53. Two people witnessed the event.
-- 2 | 2020 | 1 | 1 | Zlatkova Street | Burglary took place at 05:23. Two people witnessed the event.
-- 3 | 2020 | 1 | 1 | Bowden Boulevard | Shoplifting took place at 20:48. Two people witnessed the event.

-- ------------------------------------------------------------------------------------------------------------------------------------
SELECT description
FROM crime_scene_reports
WHERE month = 7 AND day = 28 AND street = "Chamberlin Street";
-- Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
-- Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.

-- ------------------------------------------------------------------------------------------------------------------------------------
SELECT name, transcript
FROM interviews
WHERE month = 7 AND day = 28;
-- Jose | “Ah,” said he, “I forgot that I had not seen you for some weeks.
    -- It is a little souvenir from the King of Bohemia in return for my assistance in the case of the Irene Adler papers.”
-- Eugene | “I suppose,” said Holmes, “that when Mr. Windibank came back from France he was very annoyed at your having gone to the ball.”
-- Barbara | “You had my note?” he asked with a deep harsh voice and a strongly marked German accent. “I told you that I would call.”
    -- He looked from one to the other of us, as if uncertain which to address.
-- Ruth | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away.
    -- If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
-- Eugene | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse,
    -- I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
-- Raymond | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute.
    -- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
    -- The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- ------------------------------------------------------------------------------------------------------------------------------------
SELECT license_plate, hour, minute, activity
FROM courthouse_security_logs
WHERE month = 7 AND day = 28 AND hour = 10 AND (minute > 15 AND minute < 28);
-- 5P2BI95 | 10 | 16 | exit
-- 94KL13X | 10 | 18 | exit
-- 6P58WS2 | 10 | 18 | exit
-- 4328GD8 | 10 | 19 | exit
-- G412CB7 | 10 | 20 | exit
-- L93JTIZ | 10 | 21 | exit
-- 322W7JE | 10 | 23 | exit
-- 0NTHK55 | 10 | 23 | exit

-- ------------------------------------------------------------------------------------------------------------------------------------
SELECT name, phone_number, passport_number, license_plate
FROM people
WHERE id IN (SELECT person_id
FROM bank_accounts
WHERE account_number IN (SELECT account_number
FROM atm_transactions
WHERE month = 7 AND day = 28 AND atm_location = 'Fifer Street' AND transaction_type = 'withdraw'));
-- name      | phone_number   | passport_number | license_plate
-- Bobby     | (826) 555-1652 | 9878712108      | 30G67EN
-- Elizabeth | (829) 555-5269 | 7049073643      | L93JTIZ
-- Victoria  | (338) 555-6650 | 9586786673      | 8X428L0
-- Madison.  | (286) 555-6063 | 1988161715      | 1106N58
-- Roy       | (122) 555-4581 | 4408372428      | QX4YZN3
-- Danielle  | (389) 555-5198 | 8496433585      | 4328GD8
-- Russell   | (770) 555-1861 | 3592750733      | 322W7JE
-- Ernest    | (367) 555-5533 | 5773159633      | 94KL13X

-- name      | phone_number   | passport_number | license_plate
-- Elizabeth | (829) 555-5269 | 7049073643      | L93JTIZ
-- Danielle  | (389) 555-5198 | 8496433585      | 4328GD8
-- Russell   | (770) 555-1861 | 3592750733      | 322W7JE
-- Ernest    | (367) 555-5533 | 5773159633      | 94KL13X

-- ------------------------------------------------------------------------------------------------------------------------------------
SELECT caller, receiver
FROM phone_calls
WHERE month = 7 AND day = 28 AND duration < 60;
-- caller         | receiver
-- (130) 555-0289 | (996) 555-8899
-- (499) 555-9472 | (892) 555-8872
-- (367) 555-5533 | (375) 555-8161
-- (499) 555-9472 | (717) 555-1342
-- (286) 555-6063 | (676) 555-6554
-- (770) 555-1861 | (725) 555-3243
-- (031) 555-6622 | (910) 555-3251
-- (826) 555-1652 | (066) 555-9701
-- (338) 555-6650 | (704) 555-2131

-- =>>
-- 94KL13X | 10 | 18 | exit
-- 322W7JE | 10 | 23 | exit
-- name      | phone_number   | passport_number | license_plate
-- Russell   | (770) 555-1861 | 3592750733      | 322W7JE
-- Ernest    | (367) 555-5533 | 5773159633      | 94KL13X

-- caller         | receiver
-- (770) 555-1861 | (725) 555-3243
-- (367) 555-5533 | (375) 555-8161

-- ------------------------------------------------------------------------------------------------------------------------------------
SELECT id, month, day, hour, minute, origin_airport_id, destination_airport_id
FROM flights
WHERE month = 7 AND day = 29
ORDER BY hour;
-- id | month | day | hour | minute | origin_airport_id | destination_airport_id
-- 36 | 7     | 29  | 8    | 20     | 8                 | 4
-- 43 | 7     | 29  | 9    | 30     | 8                 | 1
-- 23 | 7     | 29  | 12   | 15     | 8                 | 11
-- 53 | 7     | 29  | 15   | 20     | 8                 | 9
-- 18 | 7     | 29  | 16   | 0      | 8                 | 6

-- =>
-- id | month | day | hour | minute | origin_airport_id | destination_airport_id
-- 36 | 7     | 29  | 8    | 20     | 8                 | 4

-- ------------------------------------------------------------------------------------------------------------------------------------
SELECT id, city
FROM airports
WHERE id IN (4, 8);

-- id | city
-- 4 | London
-- 8 | Fiftyville

-- ------------------------------------------------------------------------------------------------------------------------------------
SELECT passport_number
FROM passengers
WHERE flight_id = 36;
-- passport_number
-- 7214083635
-- 1695452385
-- 5773159633
-- 1540955065
-- 8294398571
-- 1988161715
-- 9878712108
-- 8496433585


-- =>>
-- 94KL13X | 10 | 18 | exit

-- name      | phone_number   | passport_number | license_plate
-- Ernest    | (367) 555-5533 | 5773159633      | 94KL13X

-- caller         | receiver
-- (367) 555-5533 | (375) 555-8161

-- ------------------------------------------------------------------------------------------------------------------------------------
SELECT name
FROM people
WHERE phone_number = '(375) 555-8161';
-- name
-- Berthold