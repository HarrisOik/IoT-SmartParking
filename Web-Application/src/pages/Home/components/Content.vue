<template>
  <div style="margin: auto">
    <h2>What would you like to do</h2>
    <div class="container">
      <a href="spots">
        <div class="item">View Parking Spots</div>
      </a>

      <a href="register">
        <div class="item">Register RFID Card</div>
      </a>
    </div>
  </div>
</template>

<script>
export default {
  name: "Content",
};
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
a {
  color: #2c3e50;
  text-decoration: none;
}
.container {
  display: flex;
  gap: 1rem;
  line-height: 1.6rem;
  font-size: 1.5rem;
  font-weight: bold;
  flex-wrap: wrap;
}
.item {
  cursor: pointer;
  padding: 3rem;
  max-width: 12ch;
  box-shadow: 0px 3px 3px -2px rgb(0 0 0 / 20%),
    0px 3px 4px 0px rgb(0 0 0 / 14%), 0px 1px 8px 0px rgb(0 0 0 / 12%);
}
</style>
