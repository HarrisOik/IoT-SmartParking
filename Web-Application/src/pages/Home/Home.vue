<template>
  <Header />
  <Content />
  <Footer />
</template>
<script>
import Content from "./components/Content.vue";
import Header from "../../components/Header.vue";
import Footer from "../../components/Footer.vue";

export default {
  name: "Home",
  components: {
    Content,
    Header,
    Footer,
  },
};
</script>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  display: flex;
  flex-direction: column;
}
</style>
