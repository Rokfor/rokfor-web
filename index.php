<?php
	/**
	 * Initialize Session
	 */

	session_start();
	ini_set('display_errors','Off');

	/**
	 * Load main Class
	 */

	chdir(dirname(__FILE__));
	require_once('local/view.class.inc');	

	/**
	 * Load Main Class
	 */

	$s = new view();

	/**
	 * Dump HTML and Ajax
	 */

	$s->dump();

	/**
	 * Print Render Time
	 */
	
	$s->rendertime(); 
?>