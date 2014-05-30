rokfor-web
==========

A simple reference implementation of a Rokfor CMS web application.

Prerequisites: A running rokfor installation. Check it out here: <a href="/Rokfor/rokfor-cms">Rokfor-cms</a>

Installation
============

* Clone the repository in the document root
* Make sure, that the path to the Rokfor Configuration exists (rf_config-v2.inc in index.php)

How does this work
==================

Parameters
----------

This repository is a simple template engine. It accepts four GET parameters. In the constructor of controller.class.inc you see:

```
$this->_checkBook($_GET['book']);
$this->_checkIssue($_GET['issue']);
$this->_checkChapter($_GET['chapter']);		
$this->_checkElement($_GET['element']);	
```

If these parameters are omitted, the first available will be set as default.
You can send these parameters when creating a menufunction, or pretty print them with an .htaccess file

```
RewriteRule ^(.*)$ 					/index.php?book=$1 [L]
RewriteRule ^(.*)/(.*)$ 			/index.php?book=$1&issue=$2 [L]
RewriteRule ^(.*)/(.*)/(.*)$ 		/index.php?book=$1&issue=$2&chapter=$3 [L]
RewriteRule ^(.*)/(.*)/(.*)/(.*)$ 	/index.php?book=$1&issue=$2&chapter=$3&element=$4 [L]
```

Templates
---------

Templates reside in the templates folder. They are html, and you're totally free in designing whatever you want. The little magic is here:

```
<?=$dump_content?>
```

Whenever you write a snippet like this, make sure, that the function $dump_content in this example also exists in the view.class.inc file. When you design a function for a template, there are two main data structures holding the necessary data.

```
$this->tree
$this->data
```

$this->data holds the loaded template. You can create a page with it.
$this->tree holds the available books, the issues, the chapters and the elements of the current chapter. You can easily create a menu with it.

