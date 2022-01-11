<template>
  <div style="margin: auto">
    <h2>Parking Spots</h2>
    <div class="container">
      <div class="item" v-for="datum in data" :key="datum._id">
        <div>{{ datum.name }}</div>
        <div v-if="datum.status" style="color: red">Taken</div>
        <div v-else style="color: green">Free</div>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  name: "Content",
  data() {
    return {
      data: null,
    };
  },
  async mounted() {
    const baseURL = "http://localhost:3000";
    const res = await fetch(`${baseURL}/api/v1/spots`, {
      method: "GET",
    });

    const data = await res.json();

    function compare(a, b) {
      if (a.name < b.name) {
        return -1;
      }
      if (a.name > b.name) {
        return 1;
      }
      return 0;
    }

    this.data = data.spots.sort(compare);
  },
};
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
.container {
  display: flex;
  gap: 2rem;
  line-height: 1.6rem;
  font-size: 1.5rem;
  font-weight: bold;
  flex-wrap: wrap;
  justify-content: center;
  max-width: 600px;
}
.item {
  cursor: pointer;
  padding: 3rem;
  max-width: 12ch;
  box-shadow: 0px 3px 3px -2px rgb(0 0 0 / 20%),
    0px 3px 4px 0px rgb(0 0 0 / 14%), 0px 1px 8px 0px rgb(0 0 0 / 12%);
}
</style>
