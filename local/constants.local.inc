<?php
if(!defined('ROK')) die('Direct access is not allowed');

/**
 * constants: defining global constants used for all projects
 *
 * @author Urs Hofer
 */

/* Template Path */
define('template_path', getenv("DOCUMENT_ROOT")."/template");

/* Missing View Function */
define('view_missing', '<span class="vM">[view function missing]</span>');

?>
