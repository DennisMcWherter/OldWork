<?php
/**
 * Simple Sessions Tutorial by RageD
 *
 * (C) RageD 2009. All Rights Reserved.
 *
 * This has to be the first thing included in all documents for them
 * to hold session data.
 *
 * Also, (besides comments such as this) session_start(); must start this
 * this document before anything else!
 *
 */
session_start();

// Make sure people can't just go into private files :) (E.g.: functions.php)
define("AUTH_ACCEPT", true);

/**
 * Normally more information would be in here but since we're just handling
 * sessions, not much more is necessary :)
 *
 */
?>