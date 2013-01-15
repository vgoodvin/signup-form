<pre><?php print_r($debug); ?></pre>

<form action="/" method="post" id="signup-form">
  <div>
    <label for="edit-email">Email</label>
    <input type="text" name="email" id="edit-email" maxlength="60" size="60" class="form-text" value="<?php print isset($form_data['email']) ? $form_data['email'] : ''; ?>">
  </div>
  <div>
    <label for="edit-pass">Password</label>
    <input type="password" name="pass" id="edit-pass" maxlength="128" size="60" class="form-text">
  </div>
  <div>
    <label for="edit-lang">Language</label>
    <select name="lang" id="edit-lang" class="edit-select">
      <?php foreach ($languages as $code => $name): ?>
        <option value="<?php print $code; ?>" <?php print ($code == $form_data['lang']) ? 'selected' : ''; ?>><?php print $name; ?></option>
      <?php endforeach; ?>
    </select>
  </div>
  <input type="submit" name="op" id="edit-submit" value="Sign up" class="form-submit">
</form>
