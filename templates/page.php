<html>
<head>
  <title>Sign up</title>
  <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
  <link href="/public/style.css" rel="stylesheet">
  <?php //TODO: add form validation in JS ?>
</head>
<body>
  <ul id="messages">
    <?php foreach ($messages as $message):?>
      <li class="message"><?php print $message; ?></li>
    <?php endforeach; ?>
  </ul>
  <?php include_once('./templates/form.php'); ?>

  <!-- SCRIPTS -->
  <script src="/public/jquery.min.js"></script>
  <script src="/public/script.js"></script>
  <!-- /SCRIPTS -->
</body>
</html>
