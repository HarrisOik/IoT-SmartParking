<template>
  <div class="container">
    <h2>Register your card ID</h2>
    <div class="input-container">
      <input ref="get_id" />
      <button @click="registerID">Register</button>
    </div>
    <div style="margin-top: 1rem">{{ info }}</div>
  </div>
</template>

<script>
export default {
  name: "Content",
  data() {
    return {
      info: "",
    };
  },
  methods: {
    async registerID() {
      try {
        const ticket = this.$refs.get_id.value;
        const baseURL = "http://localhost:3000";
        const res = await fetch(`${baseURL}/api/v1/tickets`, {
          method: "POST",
          headers: { "Content-Type": "application/json" },
          body: JSON.stringify({ ticket }),
        });
        const data = await res.json();
        const errors = data?.msg?.errors;
        this.info = errors ? "Error" : "Ticket created successfuly.";
      } catch (err) {
        this.info = "Something went wrong";
      }
    },
  },
};
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
.container {
  display: flex;
  flex-direction: column;
  margin: auto;
  align-items: center;
  gap: 1rem;
}
.input-container {
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
