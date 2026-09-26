<script>
    let dateText = $state("Click the button to display the date");

    function updateDate() {
        dateText = `Today's Date: ${new Date().toLocaleDateString()}`;
    }
</script>

<div class="p-8 bg-gray-50 min-h-auto text-black mt-5 rounded-xl">
    <h2 class="text-xl font-semibold mb-4 text-gray-800">
        Exercise 1: Display Date on Click
    </h2>

    <button
        onclick={updateDate}
        class="px-4 py-2 bg-blue-600 text-white rounded hover:bg-blue-700 transition"
    >
        Show Date
    </button>

    <p class="mt-4 text-lg font-medium text-gray-700">{dateText}</p>
</div>
